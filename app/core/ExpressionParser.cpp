#include "ExpressionParser.h"
#include <cctype>
#include <sstream>
#include <stdexcept>

ExpressionParser::ExpressionParser(FunctionRegistry &registry)
    : registry(registry) {}

bool ExpressionParser::isOperator(const std::string &token)
{
    return registry.isOperator(token);
}

bool ExpressionParser::isFunction(const std::string &token)
{
    return registry.isFunction(token);
}

int ExpressionParser::getPriority(const std::string &op)
{
    return registry.getPriority(op);
}

std::vector<std::string> ExpressionParser::parse(const std::string &expression)
{
    std::vector<std::string> output;
    std::stack<std::string> ops;
    std::string token;
    std::string spaced;

    // пробелы вокруг операторов
    for (char c : expression)
    {
        if (std::string("()+-*/^").find(c) != std::string::npos)
        {
            spaced += ' ';
            spaced += c;
            spaced += ' ';
        }
        else
        {
            spaced += c;
        }
    }

    std::istringstream in(spaced);
    std::string prevToken;

    while (in >> token)
    {
        if (token == "-" && (prevToken.empty() || prevToken == "(" || isOperator(prevToken)))
        {
            std::string next;
            if (in >> next)
            {
                if (std::isdigit(next[0]))
                {
                    output.push_back("-" + next);
                    prevToken = next;
                    continue;
                }
                else
                {
                    ops.push("-");
                    prevToken = "-";
                    continue;
                }
            }
        }

        if (std::isdigit(token[0]))
        {
            output.push_back(token);
        }
        else if (isFunction(token))
        {
            ops.push(token);
        }
        else if (isOperator(token))
        {
            while (!ops.empty() && getPriority(ops.top()) > getPriority(token))
            {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
        else if (token == "(")
        {
            ops.push(token);
        }
        else if (token == ")")
        {
            while (!ops.empty() && ops.top() != "(")
            {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty())
                ops.pop();
        }
        else
        {
            throw std::runtime_error("Unknown token: " + token);
        }

        prevToken = token;
    }

    while (!ops.empty())
    {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}