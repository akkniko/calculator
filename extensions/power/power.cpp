#include "../include/dllModel.h"

Data getData() noexcept
{
    return {
        "^",
        3,
        false};
}

void doCalculation(StackT &stack)
{
    if (stack.size() < 2)
        throw std::runtime_error("pow: not enough operands");

    double exponent = stack.top();
    stack.pop();

    double base = stack.top();
    stack.pop();

    stack.push(std::pow(base, exponent));
}