#include "PluginLoader.h"
#include "../../include/dllData.h"
#include "../../include/dllModel.h"

PluginLoader::PluginLoader(FunctionRegistry &registry)
    : registry(registry) {}

PluginLoader::~PluginLoader()
{
    for (auto &p : loadedPlugins)
    {
        if (p.handle)
        {
            FreeLibrary(p.handle);
        }
    }
}

void PluginLoader::loadPlugins(const std::string &directory)
{
    namespace fs = std::filesystem;

    if (!fs::exists(directory))
    {
        Logger::warn("Plugins directory not found: " + directory);
        return;
    }

    for (auto &entry : fs::directory_iterator(directory))
    {
        if (entry.path().extension() == ".dll")
        {
            try
            {
                loadSinglePlugin(entry.path().string());
            }
            catch (const std::exception &ex)
            {
                Logger::error("Failed to load plugin " + entry.path().string() + ": " + ex.what());
            }
        }
    }

    if (loadedPlugins.empty())
    {
        Logger::warn("No plugins loaded from " + directory);
    }
}

void PluginLoader::loadSinglePlugin(const std::string &path)
{
    HMODULE handle = LoadLibraryA(path.c_str());
    if (!handle)
    {
        throw std::runtime_error("Cannot load library: " + path);
    }

    auto getData = reinterpret_cast<Data (*)()>(GetProcAddress(handle, "getData"));
    auto doCalculation = reinterpret_cast<void (*)(StackT &)>(GetProcAddress(handle, "doCalculation"));

    if (!getData || !doCalculation)
    {
        FreeLibrary(handle);
        throw std::runtime_error("Missing required functions in " + path);
    }

    Data info = getData();
    registry.registerFunction(info.value, doCalculation, info.priority, info.isUnary);

    Logger::info("Loaded plugin: " + info.value + " from " + path);
    loadedPlugins.push_back({handle, path});
}
