#include "../include/dllModel.h"

Data getData() noexcept
{
    return {"-", 2,   false};
}

void doCalculation(StackT &stack)
{
    if (stack.size() < 2)
    {
        throw std::runtime_error("sub: The subtraction operator requires 2 values");
    }
    double x = stack.top();
    stack.pop();
    double y = stack.top();
    stack.pop();

    stack.push(y - x);
}