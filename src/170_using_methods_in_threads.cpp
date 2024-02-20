#include <iostream>
#include <thread>

template<typename E>
class BlockquingQueue
{
public:
    void push(E e) {
        std::cout << "pushing" << std::endl;
    }

    void pop() {
        std::cout << "poping" << std::endl;
    }

};

int main()
{
    BlockquingQueue<int> q;
    std::thread t1(&BlockquingQueue<int>::push, &q, 7);
    std::thread t2(&BlockquingQueue<int>::pop, &q);

    t1.join();
    t2.join();

    return 0;
}
