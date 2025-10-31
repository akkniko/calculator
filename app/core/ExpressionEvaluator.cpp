#include "ExpressionEvaluator.h"
#include <stdexcept>
#include <cstdlib>

ExpressionEvaluator::ExpressionEvaluator(FunctionRegistry &registry)
    : registry(registry) {}

double ExpressionEvaluator::evaluate(const std::vector<std::string> &rpn)
{
    std::stack<double> st;

    for (auto &token : rpn)
    {
        if (std::isdigit(token[0]) ||
            (token.size() > 1 && std::isdigit(token[1]) && token[0] == '-'))
        {
            st.push(std::stod(token));
        }
        else
        {
            auto func = registry.getFunction(token);
            if (!func)
            {
                throw std::runtime_error("Unknown function: " + token);
            }
            func(st);
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("Invalid expression");

    return st.top();
}
