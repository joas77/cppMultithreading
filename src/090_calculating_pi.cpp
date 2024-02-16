#include <iostream>
#include <cmath>
#include <iomanip>

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
    std::cout << std::setprecision(15) << calculatePi(1e9) << std::endl;
    return 0;
}
