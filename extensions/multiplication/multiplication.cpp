#include "../include/dllModel.h"

Data getData() noexcept {
    return { 
        "*", 
        2, 
        false 
    };
}

void doCalculation(StackT& stack) {
    if (stack.size() < 2)
        throw std::runtime_error("multiplication: not enough operands");

    double b = stack.top(); 
    stack.pop();
    
    double a = stack.top();
    stack.pop();

    stack.push(a * b);
}
