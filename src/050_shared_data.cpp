#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>


int main()
{
    std::atomic<int> count = 0;
    constexpr int kIterations = 1e6;

    std::thread t1([&count](){
        for(int i = 0; i < kIterations; i++){
            ++count;
        }
    });

    std::thread t2([&count](){
        for(int i = 0; i < kIterations; i++){
            ++count;
        }
    });

    t1.join();
    t2.join();

    std::cout << count << std::endl;

    return 0;
}
