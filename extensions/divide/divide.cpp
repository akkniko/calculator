#include "../include/dllModel.h"

Data getData() noexcept
{
    return {
        "/",
        2,
        false};
}

void doCalculation(StackT &stack)
{
    if (stack.size() < 2)
        throw std::runtime_error("divide: not enough operands");

    double b = stack.top();
    stack.pop();

    double a = stack.top();
    stack.pop();

    if (b == 0.0)
        throw std::runtime_error("divide: division by zero");

    stack.push(a / b);
}
