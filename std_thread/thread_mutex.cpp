#include <assert.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// using namespace std;
int count = 0;
std::mutex mtx;

void funcLock()
{
    for (int i = 0; i < 10000; i++)
    {
        // 如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住。
        mtx.lock();
        ++count;
        mtx.unlock();
    }
}

void funcTryLock()
{
    for (int i = 0; i < 10000; i++)
    {

        // try_lock()的非阻塞特性，如果当前互斥量被其他线程锁住，
        // 则当前try_lock()返回 false，此时counter并不会增加1。
        if (mtx.try_lock())
        {
            ++count;
            mtx.unlock();
        }
    }
}

void funcLockGuard()
{
    for (int i = 0; i < 10000; i++)
    {
        // 不用配对使用,lock_guard构造函数和析构函数分别调用lock()、unlock()
        std::lock_guard<std::mutex> lxk(mtx);
        ++count;
    }
}

void funcUniqueLock()
{
    for (int i = 0; i < 10000; ++i)
    {
        // 注意此时Tag参数为std::adopt_lock表明当前线程已经获得了锁，
        // 此后mtx对象的解锁操作交由adopt_lock对象lck来管理，在lck的生命周期结束之后，
        // mtx对象会自动解锁。
        // std::adopt_lock_t assume the calling thread already has ownership of the mutex
        // std::unique_lock<std::mutex> lck(mtx, std::adopt_lock);
        // ++count;

        // std::defer_lock 表明当前线程没有获得锁
        // 需要通过lck的lock和unlock来加锁和解锁
        std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
        lck.lock();
        ++count;
        lck.unlock();
    }
}

int main()
{
    std::thread mutexTheads[10];
    for (int i = 0; i < 10; i++)
    {
        // mutexTheads[i] = std::thread(funcLock);
        // mutexTheads[i] = std::thread(funcTryLock);
        // mutexTheads[i] = std::thread(funcLockGuard);
        mutexTheads[i] = std::thread(funcUniqueLock);
    }

    for (auto &mutexThead : mutexTheads)
    {
        mutexThead.join();
    }
    std::cout << count << " successful increases of the counter" << std::endl;

    return 0;
}