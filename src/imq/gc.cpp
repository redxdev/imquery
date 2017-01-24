#include "gc.h"
#include "utility.h"

#include <iostream>
#include <algorithm>

namespace imq
{
	GCTraceable::~GCTraceable()
	{
	}

	GCObject::~GCObject()
	{
	}

	void GCObject::GC_mark()
	{
		if (!GC_bMarked)
		{
			GC_bMarked = true;
			GC_markChildren();
		}
	}

	void GCObject::GC_reset()
	{
		GC_bMarked = false;
	}

	bool GCObject::GC_isMarked() const
	{
		return GC_bMarked;
	}

	void GCObject::GC_markChildren()
	{
	}

	GarbageCollector::GarbageCollector()
	{
		for (size_t idx = 0; idx < IMQ_GC_BARRIER_BUFFER_SIZE; ++idx)
		{
			barrierBuffer[idx] = -1;
		}
	}

	void GarbageCollector::setDebugMode(bool bNewMode)
	{
		bDebugMode = bNewMode;
	}

	GCCollectionMode GarbageCollector::getCollectionMode() const
	{
		return collectionMode;
	}

	void GarbageCollector::setCollectionMode(GCCollectionMode newMode)
	{
		collectionMode = newMode;
	}

	void GarbageCollector::addRoot(GCTraceable* root)
	{
		if (root == nullptr)
			return;

		roots.insert(root);
	}

	void GarbageCollector::removeRoot(GCTraceable* root)
	{
		roots.erase(root);
	}

	void GarbageCollector::manage(GCObject* obj)
	{
		if (obj == nullptr || bCollecting)
			return;

		auto found = managed.insert(obj);
		if (found.second)
		{
			objectsToTrack.insert(obj);
		}
	}

	void GarbageCollector::unmanage(GCObject* obj)
	{
		if (bCollecting)
			return;

		if (managed.erase(obj) > 0 && objectsToTrack.find(obj) == objectsToTrack.end())
		{
			if (obj->GC_isDynamic())
			{
				dynamic.erase(obj);
			}
			else
			{
				trackedMemory -= obj->GC_getSize();
			}
		}

		objectsToTrack.erase(obj);
	}

	size_t GarbageCollector::getManagedCount() const
	{
		return managed.size();
	}

	size_t GarbageCollector::getTrackedMemory() const
	{
		size_t totalMemory = trackedMemory;
		for (auto obj : dynamic)
		{
			totalMemory += obj->GC_getSize();
		}

		return totalMemory;
	}

	size_t GarbageCollector::getCollectionBarrier() const
	{
		return collectBarrier;
	}

	bool GarbageCollector::collect(bool force)
	{
		bool bShouldCollect = force || (collectionMode != GCCollectionMode::Barriers);

		for (auto obj : objectsToTrack)
		{
			if (obj->GC_isDynamic())
			{
				dynamic.insert(obj);
			}
			else
			{
				trackedMemory += obj->GC_getSize();
			}
		}

		objectsToTrack.clear();

		if (collectionMode != GCCollectionMode::NoBarriers)
		{
			size_t totalMemory = getTrackedMemory();

			size_t barrierHits = 0;
			size_t barrierMisses = 0;
			for (size_t idx = 0; idx < IMQ_GC_BARRIER_BUFFER_SIZE; ++idx)
			{
				int32_t val = barrierBuffer[idx];
				if (val == 2)
				{
					++barrierHits;
					if (barrierHits >= IMQ_GC_BARRIER_RAISE)
						break;
				}
				else if (val == 1)
				{
					++barrierMisses;
				}
			}

			if (barrierHits >= IMQ_GC_BARRIER_RAISE)
			{
				if (collectBarrier < IMQ_GC_BARRIER_MAX)
				{
					while (collectBarrier < totalMemory + IMQ_GC_BARRIER_INCREMENT && collectBarrier < IMQ_GC_BARRIER_MAX)
					{
						collectBarrier += IMQ_GC_BARRIER_INCREMENT;
						collectBarrier = std::min(collectBarrier, IMQ_GC_BARRIER_MAX);
					}

					if (bDebugMode)
					{
						std::cout << "gc: raised gc barrier to " << collectBarrier << std::endl;
					}

					for (size_t idx = 0; idx < IMQ_GC_BARRIER_BUFFER_SIZE; ++idx)
					{
						barrierBuffer[idx] = -1;
					}
				}
			}
			else if (barrierMisses >= IMQ_GC_BARRIER_LOWER)
			{
				if (collectBarrier > IMQ_GC_BARRIER_MIN && collectBarrier - IMQ_GC_BARRIER_INCREMENT > totalMemory)
				{
					collectBarrier -= IMQ_GC_BARRIER_INCREMENT;
					collectBarrier = std::max(collectBarrier, IMQ_GC_BARRIER_MIN);

					if (bDebugMode)
					{
						std::cout << "gc: lowered gc barrier to " << collectBarrier << std::endl;
					}

					for (size_t idx = 0; idx < IMQ_GC_BARRIER_BUFFER_SIZE; ++idx)
					{
						barrierBuffer[idx] = -1;
					}
				}
			}

			if (!bShouldCollect)
			{
				if (trackedMemory > collectBarrier)
				{
					barrierBuffer[bbufNext] = 2;
					++bbufNext;
					if (bbufNext >= IMQ_GC_BARRIER_BUFFER_SIZE)
						bbufNext = 0;

					bShouldCollect = true;
				}
				else
				{
					barrierBuffer[bbufNext] = 1;
					++bbufNext;
					if (bbufNext >= IMQ_GC_BARRIER_BUFFER_SIZE)
						bbufNext = 0;
				}
			}
		}

		if (!bShouldCollect)
		{
			return false;
		}

		bCollecting = true;

		for (auto root : roots)
		{
			root->GC_mark();
		}

		if (bDebugMode)
		{
			std::cout << "gc: collecting..." << std::endl;
		}

		size_t collectedCount = 0;
		for (auto it = managed.begin(); it != managed.end();)
		{
			if (!(*it)->GC_isMarked())
			{
				GCObject* obj = *it;
				it = managed.erase(it);

				if (obj->GC_isDynamic())
				{
					dynamic.erase(obj);
				}
				else
				{
					trackedMemory -= obj->GC_getSize();
				}

				delete obj;
				++collectedCount;
			}
			else
			{
				(*it)->GC_reset();
				++it;
			}
		}

		if (bDebugMode)
		{
			std::cout << "gc: collected " << collectedCount << " objects" << std::endl;
		}

		bCollecting = false;

		return true;
	}

	ScopedRoot::ScopedRoot(GarbageCollector* gc, GCTraceable* root)
		: gc(gc), root(root)
	{
		gc->addRoot(root);
	}

	ScopedRoot::~ScopedRoot()
	{
		gc->removeRoot(root);
	}

}