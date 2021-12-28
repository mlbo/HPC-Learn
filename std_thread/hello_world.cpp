#include <iostream>
#include <thread>

void func()
{
    std::cout << "worker thread id:" << std::this_thread::get_id() << std::endl;
    std::cout << "Hello World!" << std::endl;
}

int main()
{
    std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
    std::thread workerThread(func);
    workerThread.join();

    return 0;

}