#include <iostream>
#include <thread>
#include <cmath>
#include <iomanip>
#include <future>
#include <exception>

/**
 * Calculates pi using Leibniz formula
 * pi/4 = sum from n=0 to inf (-1)^n/(2n+1)
 */
double calculatePi(int terms)
{
    if(terms < 1)
        throw std::runtime_error("Terms cannot be less than 1");

    double sum = 0.0;
    for(int i=0; i<terms; i++) {
        int sign = pow(-1, i);
        double term = 1.0 /(i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main()
{
    std::packaged_task<double(int)> task1(calculatePi);
    std::future<double> future1 = task1.get_future();

    std::thread t1(std::move(task1), 0);
    try {
        double result = future1.get();
        std::cout << std::setprecision(15) << result << std::endl;
    } catch(std::exception &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    t1.join();

    return 0;
}
