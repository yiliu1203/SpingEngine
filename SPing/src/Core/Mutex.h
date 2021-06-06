#pragma once
#include "SPingPre.h"

namespace SPing
{
	class SP_API Mutex
	{
	public:
		Mutex();
		~Mutex();
		void Acquire();
		bool TryAcquere();
		void Release();
	private:
		void* handle_;
	};


	class SP_API MutexLock
	{
	public:
		explicit MutexLock(Mutex& mutex);
		~MutexLock();
		MutexLock(MutexLock& lock) = delete;
		MutexLock& operator= (MutexLock& lock) = delete;
	private:
		Mutex& mutex_;
	};
}