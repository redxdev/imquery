#include "gc.h"

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

		managed.insert(obj);
	}

	void GarbageCollector::unmanage(GCObject* obj)
	{
		if (bCollecting)
			return;

		managed.erase(obj);
	}

	size_t GarbageCollector::getManagedCount() const
	{
		return managed.size();
	}

	void GarbageCollector::collect(bool force)
	{
		bCollecting = true;

		for (auto root : roots)
		{
			root->GC_mark();
		}

		for (auto it = managed.begin(); it != managed.end();)
		{
			if (!(*it)->GC_isMarked())
			{
				GCObject* obj = *it;
				it = managed.erase(it);
				delete obj;
			}
			else
			{
				(*it)->GC_reset();
				++it;
			}
		}

		bCollecting = false;
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