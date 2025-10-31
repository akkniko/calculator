#pragma once
#include <string>
#include <map>
#include <stack>
#include <functional>
#include "../../include/dllData.h"

using StackT = std::stack<double>;
using DoMathFunc = void (*)(StackT &);

struct FunctionData
{
    DoMathFunc func;
    unsigned char priority;
    bool isUnary;
    bool isFunction;
};

class FunctionRegistry
{
public:
    void registerFunction(const std::string &name, DoMathFunc func,
                          unsigned char priority, bool isUnary);

    DoMathFunc getFunction(const std::string &name);
    bool isOperator(const std::string &name) const;
    bool isFunction(const std::string &name) const;
    int getPriority(const std::string &name) const;

private:
    std::map<std::string, FunctionData> functions;
};
