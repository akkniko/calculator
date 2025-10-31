#include "../include/dllModel.h"

Data getData() noexcept {
    return { 
        "!",
         4, 
         true
         }; 
}

void doCalculation(StackT& stack) {
    if (stack.empty())
        throw std::runtime_error("factorial: stack underflow");

    double x = stack.top();
    stack.pop();

    if (x < 0)
        throw std::runtime_error("factorial: negative number");

    double result = 1;
    for (int i = 1; i <= static_cast<int>(x); ++i)
        result *= i;

    stack.push(result);
}
