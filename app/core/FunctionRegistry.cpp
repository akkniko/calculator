#include "FunctionRegistry.h"
#include <stdexcept>

void FunctionRegistry::registerFunction(const std::string &name, DoMathFunc func,
                                        unsigned char priority, bool isUnary)
{
    FunctionData data{func, priority, isUnary, !isUnary && std::isalpha(name[0])};
    functions[name] = data;
}

DoMathFunc FunctionRegistry::getFunction(const std::string &name)
{
    auto it = functions.find(name);
    if (it == functions.end())
        throw std::runtime_error("Function not found: " + name);
    return it->second.func;
}

bool FunctionRegistry::isOperator(const std::string &name) const
{
    auto it = functions.find(name);
    return it != functions.end() && !it->second.isFunction;
}

bool FunctionRegistry::isFunction(const std::string &name) const
{
    auto it = functions.find(name);
    return it != functions.end() && it->second.isFunction;
}

int FunctionRegistry::getPriority(const std::string &name) const
{
    auto it = functions.find(name);
    if (it == functions.end())
        return 0;
    return it->second.priority;
}
