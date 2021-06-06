#include "Thread.h"



namespace SPing
{

	static DWORD WINAPI StaticThreadFunction(void* data)
	{
		Thread* t = static_cast<Thread*>(data);
		t->ThreadFunction();
		return 0;
	}

	ThreadID Thread::mainThreadID_;


	Thread::Thread() : handle_(nullptr)
	{
	}

	Thread::~Thread()
	{
		Stop();
	}

	bool Thread::Run()
	{
		if (handle_)
			return false;
		#ifdef _WIN32
			handle_ = CreateThread(nullptr, 0, StaticThreadFunction, this, 0, nullptr);
		#endif // _WIN32
			return handle_ != nullptr;
	}

	bool Thread::Stop()
	{
		if (!handle_)
			return false;
		#ifdef _WIN32
			WaitForSingleObject((HANDLE)handle_, INFINITE);
			CloseHandle((HANDLE)handle_);
		#endif
		handle_ = nullptr;
		return true;
	}

	void Thread::SetMainThread()
	{
		Thread::mainThreadID_ = GetCurThreadID();

	}

	ThreadID Thread::GetCurThreadID()
	{
		#ifdef _WIN32
		return GetCurrentThreadId();
		#endif
		return 0;
	}

	bool Thread::IsMainThread()
	{
		return GetCurThreadID() == Thread::mainThreadID_;
	}

}