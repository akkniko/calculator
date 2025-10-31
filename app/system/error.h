#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

// Базвое исключение калькулятора
class CalculatorError : public std::runtime_error
{
public:
    explicit CalculatorError(const std::string &message)
        : std::runtime_error(message) {}
};

// Ошибка при загрузке плагина
class PluginError : public CalculatorError
{
public:
    explicit PluginError(const std::string &message)
        : CalculatorError("Plugin Error: " + message) {}
};

// Ошибка при разборе выражения
class ParseError : public CalculatorError
{
public:
    explicit ParseError(const std::string &message)
        : CalculatorError("Parse Error: " + message) {}
};

// Ошибка во время вычисления
class EvaluationError : public CalculatorError
{
public:
    explicit EvaluationError(const std::string &message)
        : CalculatorError("Evaluation Error: " + message) {}
};

#endif // ERROR_H