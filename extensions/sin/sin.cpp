#define _USE_MATH_DEFINES
#include "../include/dllModel.h"

Data getData() noexcept
{
    return {"sin", 5, true};
}

void doCalculation(StackT &stack)
{
    if (stack.empty())
        throw std::runtime_error("sin: stack empty");

    double x = stack.top();
    stack.pop();

    stack.push(std::sin(x * M_PI / 180.0)); // sinus в градусах
}
