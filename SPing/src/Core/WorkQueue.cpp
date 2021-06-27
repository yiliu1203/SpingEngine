#include "SPingPre.h"
#include "WorkQueue.h"
#include "algorithm"

namespace SPing
{
	unsigned WorkQueue::priority = 0;

	WorkQueue::WorkQueue(Context* context) : Object(context)
	{
	}

	WorkQueue::~WorkQueue()
	{
		for (size_t i = 0; i < thread_.size(); i++)
		{
			thread_[i]->Stop();
		}
		thread_.clear();
	}

	void WorkQueue::CreateThreads(unsigned count)
	{
		SP_ASSERT(thread_.empty() == true, "Error");
		for (unsigned i = 0; i < count; i++)
		{
			std::shared_ptr<WorkerThread> t = std::make_shared<WorkerThread>(this, i);
			thread_.push_back(t);
			t->Run();
		}
	}
	void WorkQueue::AddWorkItem(std::shared_ptr<WorkItem>& workItem)
	{
		workItems_.push_back(workItem);
		MutexLock lock(queueMutex_);
		workItem->priority = WorkQueue::priority++;
		preMap_[workItem->priority] = workItem.get();
	}

	void WorkQueue::removeWorkItem(std::shared_ptr<WorkItem>& workItem)
	{
		auto target = std::find(workItems_.begin(), workItems_.end(), workItem);
		if (target != workItems_.end())
		{
			MutexLock lock(queueMutex_);
			auto targetInMap = preMap_.find(workItem->priority);
			target = std::find(workItems_.begin(), workItems_.end(), workItem);
			if (target != workItems_.end() && targetInMap != preMap_.end())
			{
				workItems_.erase(target);
				preMap_.erase(workItem->priority);
			}
		}
	}

	void WorkQueue::ProcessItems(unsigned index)
	{
		std::cout << "ProcessItems" << index << std::endl;
		queueMutex_.Acquire();
		if (preMap_.empty())
		{
			queueMutex_.Release();
			Sleep(0);
			return;
		}
		else
		{

			std::cout << "isEmpty" << (preMap_.begin() == preMap_.end());
			auto item = preMap_.begin();
			// 要先获取 这个指针，erase 之后 这个iter 就失效了
			WorkItem* workItem = item->second;
			preMap_.erase(item->first);
			queueMutex_.Release();
			workItem->workFunction_(workItem, index);
			workItem->completed_ = true;
		}
			
	}

	void WorkQueue::PurgeCompleted()
	{
		unsigned i = 0;
		for (auto& iter= workItems_.begin(); iter!=workItems_.end();)
		{
			if ((*iter)->completed_)
				iter = workItems_.erase(iter);
			else
				iter++;
		}
	}

	void WorkQueue::HandleBeginFrame()
	{
		PurgeCompleted();
	}


	WorkerThread::WorkerThread(WorkQueue* owner, unsigned index): owner_(owner), index_(index)
	{
	}

}