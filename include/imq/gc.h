#pragma once

#include "platform.h"

#include <unordered_set>

// These don't restrict the amount of memory in use, but restrict when the GC will run collection.
#define IMQ_GC_BARRIER_MIN ((size_t)16400000)
#define IMQ_GC_BARRIER_MAX ((size_t)1500000000)
#define IMQ_GC_BARRIER_INCREMENT ((size_t)IMQ_GC_BARRIER_MIN/4)
#define IMQ_GC_BARRIER_RAISE (10)
#define IMQ_GC_BARRIER_LOWER (12)
#define IMQ_GC_BARRIER_BUFFER_SIZE (30)

namespace imq
{
	class IMQ_API GCTraceable
	{
	public:
		virtual ~GCTraceable();
		virtual void GC_mark() = 0;
	};

	class IMQ_API GCObject : public GCTraceable
	{
	public:
		virtual ~GCObject();

		// This should be overridden to get the size of just this object.
		virtual size_t GC_getSize() const = 0;
		virtual bool GC_isDynamic() const = 0;

		virtual void GC_mark() override final;
		
		void GC_reset();

		bool GC_isMarked() const;

	protected:
		virtual void GC_markChildren();

	private:
		bool GC_bMarked = false;
	};

	enum class IMQ_API GCCollectionMode
	{
		// Disable barrier functionality altogether and always run collections.
		NoBarriers,

		// The default, collections will run when a barrier is triggered.
		Barriers,

		// Always run collections, but also update barriers.
		Always
	};

	/*
	This is a very basic mark + sweep garbage collector with some simple metrics. All GC objects provide an estimated size of themselves to
	the GC. When the total estimated size of all managed objects is above a certain barrier, then the next collect() call will cause a collection
	cycle.

	Every few calls to collect(), the GC recalculates the total estimated size of all objects. This is augmented by calls to managed() and unmanage(), which
	also affect the estimated memory usage.

	If too many collection cycles happen in a short period of time, the collection barrier is raised to a new value. On the other hand, if the barrier isn't reached within a certain number of
	collect() calls, the barrier is lowered.
	*/
	class IMQ_API GarbageCollector
	{
	public:
		GarbageCollector();

		void setDebugMode(bool bNewMode);

		GCCollectionMode getCollectionMode() const;
		void setCollectionMode(GCCollectionMode newMode);

		void addRoot(GCTraceable* root);
		void removeRoot(GCTraceable* root);

		void manage(GCObject* obj);
		void unmanage(GCObject* obj);

		size_t getManagedCount() const;
		size_t getTrackedMemory() const; // bytes
		size_t getCollectionBarrier() const; // bytes

		bool collect(bool force = false);

	private:
		bool bDebugMode = false;

		GCCollectionMode collectionMode = GCCollectionMode::NoBarriers;

		std::unordered_set<GCTraceable*> roots;
		std::unordered_set<GCObject*> managed;
		std::unordered_set<GCObject*> dynamic;
		bool bCollecting = false;

		std::unordered_set<GCObject*> objectsToTrack;
		size_t trackedMemory = 0;

		size_t collectBarrier = IMQ_GC_BARRIER_MIN;
		int32_t barrierBuffer[IMQ_GC_BARRIER_BUFFER_SIZE];
		size_t bbufNext = 0;
	};

	class IMQ_API ScopedRoot
	{
	public:
		ScopedRoot(GarbageCollector* gc, GCTraceable* root);
		~ScopedRoot();

	private:
		GCTraceable* root;
		GarbageCollector* gc;
	};
}