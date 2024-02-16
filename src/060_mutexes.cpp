#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>


int main()
{
    int count = 0;
    constexpr int kIterations = 1e6;

    std::mutex mtx;

    auto func = [&](){
        for(int i = 0; i < kIterations; i++){
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << count << std::endl;

    return 0;
}
