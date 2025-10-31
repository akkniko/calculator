#include <iostream>
#include <string>
#include "core/ExpressionParser.h"
#include "core/ExpressionEvaluator.h"
#include "core/FunctionRegistry.h"
#include "system/PluginLoader.h"
#include "system/Logger.h"
#include "system/Error.h"

int main()
{
    try
    {
        FunctionRegistry registry;
        PluginLoader loader(registry);

        loader.loadPlugins("./plugins");

        ExpressionParser parser(registry);
        ExpressionEvaluator evaluator(registry);

        Logger::info("Calculator ready. Type 'exit' to quit.");

        std::string input;
        while (true)
        {
            std::cout << ">>> ";
            std::getline(std::cin, input);
            if (input == "exit")
                break;

            try
            {
                auto rpn = parser.parse(input);

                std::cout << "RPN: ";
                for (auto &t : rpn)
                    std::cout << t << " ";
                std::cout << std::endl;

                double result = evaluator.evaluate(rpn);
                std::cout << "Result: " << result << std::endl;
            }
            catch (const std::exception &e)
            {
                Logger::error(e.what());
            }
        }
    }
    catch (const std::exception &e)
    {
        Logger::error(std::string("Fatal: ") + e.what());
        return 1;
    }

    return 0;
}
