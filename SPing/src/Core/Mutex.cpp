#include "SPingPre.h"
#include "Mutex.h"

namespace SPing
{
#ifdef _WIN32
	Mutex::Mutex(): handle_(new CRITICAL_SECTION){
		InitializeCriticalSection((CRITICAL_SECTION*)handle_);
	}

	Mutex::~Mutex()
	{
		CRITICAL_SECTION* cs = (CRITICAL_SECTION*)handle_;
		DeleteCriticalSection(cs);
		delete cs;
		handle_ = nullptr;
	}
	
	void Mutex::Acquire()
	{
		EnterCriticalSection((CRITICAL_SECTION*)handle_);
	}

	bool Mutex::TryAcquere()
	{
		return TryEnterCriticalSection((CRITICAL_SECTION*)handle_) != FALSE;
	}

	void Mutex::Release()
	{
		LeaveCriticalSection((CRITICAL_SECTION*)handle_);
	}

	MutexLock::MutexLock(Mutex& mutex) :
		mutex_(mutex)
	{
		mutex_.Acquire();
	}

	MutexLock::~MutexLock()
	{
		mutex_.Release();
	}


#endif
}
