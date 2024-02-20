#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>

int main()
{
    std::condition_variable condition;
    std::mutex mtx;

    bool ready = false;
    std::thread t1([&](){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "t1 acquiring lock" << std::endl;
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "t1 acquired lock" << std::endl;
        ready = true; 
        lock.unlock();
        std::cout << "t1 rekeased lock, notifying" << std::endl;
        condition.notify_one();
    });

    std::cout << "main thread acquiring lock" << std::endl;
    std::unique_lock<std::mutex> lock(mtx);

    std::cout << "main thread acquired lock, waiting" << std::endl;
    condition.wait(lock, [&](){ return ready; });

    std::cout << "main thread finished waiting" << std::endl;
    std::cout << "ready" << ready << std::endl;
    t1.join();

    return  0;
}
