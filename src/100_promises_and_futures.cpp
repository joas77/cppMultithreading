#include <iostream>
#include <thread>
#include <cmath>
#include <iomanip>
#include <future>

/**
 * Calculates pi using Leibniz formula
 * pi/4 = sum from n=0 to inf (-1)^n/(2n+1)
 */
double calculatePi(int terms)
{
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
        auto result = calculatePi(terms);
        promise.set_value(result);
    };

    std::thread t1(doCalculation, 1E8);
    std::future<double> future = promise.get_future();
    std::cout << std::setprecision(15) << future.get() << std::endl;
    t1.join();
    return 0;
}
