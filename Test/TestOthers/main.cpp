
#include "SPingPre.h"
#include "Core/Thread.h"
#include "Core/WorkQueue.h"

void workFunction(const SPing::WorkItem* workItem, unsigned idx)
{
	std::cout << "workFunction " << idx << std::endl;

}


void workFunction2(const SPing::WorkItem* workItem, unsigned idx)
{
	std::cout << "workFunction " << idx << std::endl;
}


int main()
{
	std::cout << "Hello" << std::endl;
	SPing::WorkQueue workQueue;
	
	std::shared_ptr<SPing::WorkItem> item1 = std::make_shared<SPing::WorkItem>();
	item1->workFunction_ = workFunction;
	workQueue.AddWorkItem(item1);

	std::shared_ptr<SPing::WorkItem> item2 = std::make_shared<SPing::WorkItem>();
	item1->workFunction_ = workFunction2;
	workQueue.AddWorkItem(item2);


	workQueue.CreateThreads(10);

	

	for (size_t i = 0; i < 10; i++)
		Sleep(100);



	std::cout << workQueue.priority << std::endl;

}