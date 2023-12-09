#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>

/**
 * 一个最简单的线程池的实现
*/


// -------简单的线程安全队列--------------------
/**
 * 线程安全的队列1
*/

template <typename T>
class ThreadsafeQueue {

public:
    ThreadsafeQueue() {}

    void push(T value)
    {
        std::lock_guard<std::mutex> lk(_mutex);
        _queue.push(std::move(value));
        _cond.notify_one();
    }

    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(_mutex);  // 这里为啥时 unique_lock
        _cond.wait(lk, [this] {return !this->_queue.empty(); });
        value = std::move(_queue.front());
        _queue.pop();
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(_mutex);
        if (_queue.empty()) {
            return false;
        }
        value = std::move(_queue.front());
        _queue.pop();
        return true;
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lk(_mutex);
        return _queue.empty();
    }

private:

    mutable std::mutex _mutex;
    std::queue<T> _queue;
    std::condition_variable _cond;
};


class JoinThreads
{

public:

    explicit JoinThreads(std::vector<std::thread>& threads) : _threads{ threads }
    {
    }

    ~JoinThreads() {
        for (auto& item : _threads) {
            if (item.joinable()) {
                item.join();
            }
        }
    }

private:
    std::vector<std::thread>& _threads;
};

ThreadsafeQueue<int> g_queue;

void producer() {
    for (int i = 0; i < 3; ++i) {
        g_queue.push(i);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
void consumer1() {
    while (1) {
        int val;
        g_queue.try_pop(val);
        std::printf("[1]  -------   %d\n", val);
    }
}
void consumer2() {
    while (1) {
        int val;
        auto front = g_queue.try_pop(val);
        std::printf("[2]  -------   %d\n", front ? val : -1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/**
 *
    std::thread t1(producer);
    std::thread t2(consumer1);
    t1.join();
    t2.join();
*/

// -------简单的线程安全队列-----------------

// -------最简化的线程池----------------------

class ThreadPool0
{
public:
    ThreadPool0() :_done{ false }, _joiner{ _threads }
    {
        const size_t threadCount = std::thread::hardware_concurrency();
        try
        {
            for (size_t i = 0; i < threadCount; i++) {
                _threads.emplace_back(std::bind(&ThreadPool0::WorkThread, this));
            }
        }
        catch (...)
        {
            _done = true;
            throw;
        }
    }

    ~ThreadPool0() {
        _done = true;
    }

    template <typename FunctionType>
    void sumit(FunctionType f) {
        _workQueue.push(std::function<void()>{f});
    }


private:
    ThreadsafeQueue<std::function<void()>> _workQueue;
    std::vector<std::thread> _threads;
    JoinThreads _joiner;
    std::atomic_bool _done;

    void WorkThread()
    {
        while (!_done)
        {
            std::function<void()> task;
            if (_workQueue.try_pop(task)) {
                task();
            }
            else {
                std::this_thread::yield();
            }
        }
    }
};


ThreadPool0 pool;
// ---------最简化的线程池实现-----------------------

int main()
{
    std::cout << "Hello World" << std::endl;

    {
        // 生产者消费者模型测试线程安全队列
        // std::thread t1(producer);
        // std::thread t2(consumer1);
        // t1.join();
        // t2.join();
    }

    {
        // 最简单的线程池
        pool.sumit([]() {std::cout << "1"; });
        pool.sumit([]() {std::cout << "2"; });
        pool.sumit([]() {std::cout << "3"; });
    }

    system("pause");



    return 0;
}