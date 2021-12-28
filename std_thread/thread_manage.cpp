#include <assert.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// sleep
#include <unistd.h>

void func()
{
    std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;
    sleep(2);
    std::cout << "Hello World!" << std::endl;
}

void funcParam(int i, std::string const &s)
{
    std::cout << "worker thread1 ID:" << std::this_thread::get_id() << std::endl;
    std::cout << "Hello World! " << s << " " << i << std::endl;
}

class MyFunc
{
public:
    void operator()()
    {
        func();
    }
};

int main()
{
    std::cout << "main thread ID:" << std::this_thread::get_id() << std::endl;
    // pass object
    MyFunc myfunc;
    std::thread workerThreadDetach(myfunc);
    //使用detach()会让线程在后台运行，也就是说主线程不会等待workerThreadDetach结束。
    workerThreadDetach.detach();

    //如果线程detach(),不可能有std::thread对象能引用它，而且不能再调用该线程的join()方法。
    assert(!workerThreadDetach.joinable());
    // workerThreadDetach.join();

    // pass param
    std::string str = "at";
    std::thread workerThreadParam(funcParam, 20211228, str);
    workerThreadParam.join();

    //等待workerThreadDetach执行结束
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}