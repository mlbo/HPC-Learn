#include <assert.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <condition_variable>
#include <queue>

int counter = 0;
std::mutex mtx;
std::queue<int> dataQuene;
std::condition_variable dataCondition;
void func_preparation()
{
    for (int i = 0; i < 4; ++i)
    {
        std::unique_lock<std::mutex> lck(mtx);
        ++counter;
        dataQuene.push(counter);
        dataCondition.notify_one();
    }
}

void func_processing()
{
    while (true)
    {
        std::unique_lock<std::mutex> lck(mtx);
        std::cout << "Wait" << std::endl;
        dataCondition.wait(lck, []
                           { return !dataQuene.empty(); });
        int num = dataQuene.front();
        std::cout << "num= " << num << std::endl;
        dataQuene.pop();
        lck.unlock();
    }
}

int main()
{
    std::thread workerThreadPreparation(func_preparation);
    workerThreadPreparation.detach();
    std::thread workerThreadProcessing(func_processing);
    workerThreadProcessing.detach();
    // std::thread workerThreadProcessing1(func_processing);
    // workerThreadProcessing1.detach();

    do
    {
        std::cout << "Press the Enter key to continue.\n";
    } while (std::cin.get() != '\n');

    return 0;
}