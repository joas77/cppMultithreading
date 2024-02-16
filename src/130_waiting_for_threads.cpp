#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

int main()
{
    std::atomic<bool> ready = false;
    std::thread t1([&](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        ready = true; 
    });

    t1.join();

    while(!ready) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    std::cout << "ready" << std::endl;

    return  0;
}
