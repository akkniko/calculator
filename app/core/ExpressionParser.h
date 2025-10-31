#pragma once
#include <string>
#include <vector>
#include <stack>
#include "FunctionRegistry.h"

class ExpressionParser
{
public:
    explicit ExpressionParser(FunctionRegistry &registry);
    std::vector<std::string> parse(const std::string &expression);

private:
    FunctionRegistry &registry;
    int getPriority(const std::string &op);
    bool isOperator(const std::string &token);
    bool isFunction(const std::string &token);
};
