#pragma once
#include <vector>
#include <string>
#include <stack>
#include "FunctionRegistry.h"

class ExpressionEvaluator
{
public:
    explicit ExpressionEvaluator(FunctionRegistry &registry);
    double evaluate(const std::vector<std::string> &rpn);

private:
    FunctionRegistry &registry;
};
