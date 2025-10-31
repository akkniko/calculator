#include "../include/dllModel.h"

Data getData() noexcept
{
    return {
        "ln",
        1,
        false};
}

void doCalculation(StackT &stack)
{
    if (stack.empty())
    {
        throw std::runtime_error("ln: requires 1 value on the stack");
    }

    double x = stack.top();
    stack.pop();

    if (x <= 0)
    {
        throw std::runtime_error("ln: argument must be > 0");
    }

    stack.push(std::log(x));
}