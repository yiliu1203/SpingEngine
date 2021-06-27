
#include "SPingPre.h"
#include "Core/Thread.h"
#include "Core/WorkQueue.h"
#include "Core/Delegate.h"
#include "Core/Context.h"
#include "Core/ComponentBase.h"

void workFunction(const SPing::WorkItem* workItem, unsigned idx)
{
	std::cout << "workFunction " << idx << std::endl;

}


void workFunction2(const SPing::WorkItem* workItem, unsigned idx)
{
	std::cout << "workFunction " << idx << std::endl;
}


int add(int a, int b)
{
	return a + b;
}

int main()
{
	std::cout << "Hello" << std::endl;
	SPing::Context context;
	// test WorkQueue
	SPing::WorkQueue workQueue(static_cast<SPing::Context*> (&context) );
	
	std::shared_ptr<SPing::WorkItem> item1 = std::make_shared<SPing::WorkItem>();
	item1->workFunction_ = workFunction;
	workQueue.AddWorkItem(item1);

	std::shared_ptr<SPing::WorkItem> item2 = std::make_shared<SPing::WorkItem>();
	item2->workFunction_ = workFunction2;
	workQueue.AddWorkItem(item2);
	workQueue.CreateThreads(10);

	
	for (size_t i = 0; i < 10; i++)
		Sleep(100);


	auto d = Delegate2<int, int, int>::FromFun<&add>();
	std::cout << "add(1 + 1):" << d.Execute(1, 1) << std::endl;

	std::cout << workQueue.priority << std::endl;

	// test Context & ObjectFactory
	//context.RegisterFactory<SPing::ComponentBase>();
	SPing::ComponentBase t(static_cast<SPing::Context*> (&context));
	auto impl = new SPing::ObjectFactoryImpl<SPing::ComponentBase>(static_cast<SPing::Context*> (&context));
	context.RegisterFactory(std::shared_ptr<SPing::ObjectFactory>(impl));

}