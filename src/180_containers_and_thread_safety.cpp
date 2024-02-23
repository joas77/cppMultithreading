#include <iostream>
#include <thread>
#include <queue>

template<typename E>
class BlockquingQueue
{
private:
    int max_size_;
    std::queue<E> queue_;

public:
    BlockquingQueue(int max_size): max_size_{max_size} {}

    void push(E e) {
        queue_.push(e);
    }

    E pop() {
        E item = queue_.front();
        queue_.pop();
        return item;
    }

};

int main()
{
    BlockquingQueue<int> q(5);
    std::thread t1([&]{
        for(int i=0; i < 1e6; i++) {
            q.push(i);
            //std::cout << "pushed " << i <<" to the queue" << std::endl;
        }
    });

    std::thread t2([&]{
        for(int i=0; i<1e6; i++) {
            //std::cout << "consumend " << q.pop() << std::endl;
        }
    });

    t1.join();
    t2.join();
    std::cout << "threads finished!" << std::endl;

    return 0;
}
