#ifndef SP_THREAD_H
#define SP_THREAD_H
#include "SPingPre.h"

using ThreadID = unsigned;

namespace SPing {

	class SP_API Thread
	{
	public:
		Thread();
		virtual ~Thread();
		virtual void ThreadFunction() = 0;
		bool Run();
		bool Stop();

		static void SetMainThread();
		static ThreadID GetCurThreadID();
		static bool IsMainThread();
	private:
		void* handle_;
		static ThreadID mainThreadID_;
	};
}

#endif