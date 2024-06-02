#include "lux/math/optimization/gradient_descent.hpp"

#include <iostream>
#include <chrono>

using namespace lux::math;

Point<2, double> rosenbrock_grad(const Point<2, double>& point)
{
    double x1 = point[0];
    double x2 = point[1];
    double grad_x1 = -2 * (1 - x1) - 400 * x1 * (x2 - x1 * x1);
    double grad_x2 = 200 * (x2 - x1 * x1);
    return Point<2, double>{grad_x1, grad_x2};
}

int main()
{
    Point<2, double> initial_point{ -1.2, 1.0 };
    double learning_rate = 0.001;
    double tolerance = 1e-6;
    size_t max_iterations = 10000;

    auto start = std::chrono::high_resolution_clock::now();
    auto result = gradient_descent(initial_point, rosenbrock_grad, learning_rate, tolerance, max_iterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Minimum point: (" << result.point[0] << ", " << result.point[1] << ")\n";
    std::cout << "Number of iterations: " << result.iterations << "\n";
    std::cout << "Execution time: " << duration.count() << " seconds\n";
    return 0;
}