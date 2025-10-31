#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>
#include "../core/FunctionRegistry.h"
#include "Logger.h"
#include "Error.h"

class PluginLoader
{
public:
    explicit PluginLoader(FunctionRegistry &registry);
    ~PluginLoader();

    void loadPlugins(const std::string &directory);

private:
    struct PluginHandle
    {
        HMODULE handle;
        std::string path;
    };

    std::vector<PluginHandle> loadedPlugins;
    FunctionRegistry &registry;

    void loadSinglePlugin(const std::string &path);
};
