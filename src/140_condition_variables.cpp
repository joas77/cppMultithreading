#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>

int main()
{
    std::condition_variable condition;
    std::mutex mtx;

    std::atomic<bool> ready = false;
    std::thread t1([&](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::unique_lock<std::mutex> lock(mtx);
        ready = true; 
        lock.unlock();
        condition.notify_one();
    });

    std::unique_lock<std::mutex> lock(mtx);

    while(!ready) {
        condition.wait(lock);
    }

    std::cout << "ready" << ready << std::endl;
    t1.join();

    return  0;
}
