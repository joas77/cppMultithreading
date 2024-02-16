#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

class App {
public:
    void operator()() {
        constexpr int kIterations = 1e6;
        for(int i = 0; i < kIterations; i++) {
            std::lock_guard<std::mutex> guard(mtx);
            ++count;
        }
    }

    int getCount() {
        return count;
    }

private:
    int count=0;
    std::mutex mtx;
};

int main()
{
    App app;

    std::thread t1(std::ref(app));
    std::thread t2(std::ref(app));

    t1.join();
    t2.join();

    std::cout << app.getCount() << std::endl;

    return 0;
}
