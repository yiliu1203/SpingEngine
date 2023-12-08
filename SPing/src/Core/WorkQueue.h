#pragma once
#include "SPingPre.h"

#include "Mutex.h"
#include "Thread.h"
#include "Object.h"
#include <map>

namespace SPing
{
	class Context;

	class SP_API WorkItem
	{
		using WorkFunctionPtr = void(*)(const WorkItem*, unsigned);
	public:
		WorkFunctionPtr workFunction_;
		std::atomic<bool> completed_{};
		unsigned priority;

	};

	class SP_API WorkQueue : public Object
	{
		TYPE_RTTI(WorkQueue, Object)
		friend class WorkerThread;
		static unsigned priority;
	public:
		WorkQueue(Context* context);
		~WorkQueue();
		void CreateThreads(unsigned count);
		void AddWorkItem(std::shared_ptr<WorkItem>& workItem);
		void removeWorkItem(std::shared_ptr<WorkItem>& workItem);

	private:
		
		void ProcessItems(unsigned index);
		void PurgeCompleted();
		void HandleBeginFrame();

		std::vector<std::shared_ptr<Thread>> thread_;
		std::vector<std::shared_ptr<WorkItem>> poolItems_;
		std::vector<std::shared_ptr<WorkItem>> workItems_;
		std::map<unsigned, WorkItem*> preMap_;

		Mutex queueMutex_;

	};


	class SP_API WorkerThread : public Thread
	{
	public:
		WorkerThread(WorkQueue* owner, unsigned index);
		unsigned GetIndex() { return index_; }
		void ThreadFunction() override
		{
			owner_->ProcessItems(index_);
		}
	private:
		WorkQueue* owner_;
		unsigned index_;

	};

}
