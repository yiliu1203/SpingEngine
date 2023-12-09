#include <iostream>
#include <thread>
#include <atomic>



/** 
 * Thread ：移交线程归属权（移动构造）
 * 体会下面 ThreadGuard 和 ScopedThread 的区别
*/


class ThreadGuard
{

public:
    explicit ThreadGuard(std::thread & t) :_t(t)
    {}
    ~ThreadGuard() {
        if (_t.joinable()) {
            _t.join();
        }
    }
    ThreadGuard(const ThreadGuard& ) = delete;
    ThreadGuard& operator= (const ThreadGuard &) = delete;

private:
    std::thread& _t;
};

class ScopedThread {
public:
    explicit ScopedThread (std::thread&& t): _t(std::move(t)) {
        if (!_t.joinable()) {
            throw std::logic_error("No Thread");
        }
    }

    ~ScopedThread() {
        _t.join();
    }

    ScopedThread(const ScopedThread&) = delete;
    ScopedThread& operator= (const ScopedThread&) = delete;

private:
    std::thread _t;

};

/**
 * 1. ScopedThread 使用移动语义转移线程归属权，相比ThreadGuard更加安全，外部不再能使用参数Thread
 * 2. 构造时就判断了Thread的可用性
 * 3. 有了移动语义， 容器可以方便的装载Thread
 * 
 * 有几点需要注意：
 * 1. join 只能调用一次
 * 2. 一旦底层线程创建好后就有可能开始执行工作线程了， 真正join时 可能已经执行完，也可以能需要等待子线程。如果已经执行完， 应该时立即返回的？ 
 * 
*/

//----------------------------


int main()
{
    std::cout << "Hello World" << std::endl;


    std::cout << std::thread::hardware_concurrency();

}