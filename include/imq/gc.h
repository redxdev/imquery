#pragma once

#include "platform.h"

#include <unordered_set>

namespace imq
{
	class GCTraceable
	{
	public:
		virtual ~GCTraceable();
		virtual void GC_mark() = 0;
	};

	class GCObject : public GCTraceable
	{
	public:
		virtual ~GCObject();

		// This should be overridden to get the size of just this object.
		virtual size_t GC_getSize() const = 0;

		virtual void GC_mark() override final;
		
		void GC_reset();

		bool GC_isMarked() const;

	protected:
		virtual void GC_markChildren();

	private:
		bool GC_bMarked = false;
	};

	class GarbageCollector
	{
	public:
		void addRoot(GCTraceable* root);
		void removeRoot(GCTraceable* root);

		void manage(GCObject* obj);
		void unmanage(GCObject* obj);

		size_t getManagedCount() const;

		void collect(bool force = false);

	private:
		std::unordered_set<GCTraceable*> roots;
		std::unordered_set<GCObject*> managed;
		bool bCollecting = false;
	};

	class ScopedRoot
	{
	public:
		ScopedRoot(GarbageCollector* gc, GCTraceable* root);
		~ScopedRoot();

	private:
		GCTraceable* root;
		GarbageCollector* gc;
	};
}