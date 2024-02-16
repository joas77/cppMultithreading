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
    std::promise<double> promise;

    auto doCalculation = [&](int terms){
        try {
            auto result = calculatePi(terms);
            promise.set_value(result);
        } catch(...) {
            promise.set_exception(std::current_exception());
        }
    };

    std::thread t1(doCalculation, 1e6);
    std::future<double> future = promise.get_future();

    try {
        std::cout << std::setprecision(15) << future.get() << std::endl;
    } catch(const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    t1.join();

    return 0;
}
