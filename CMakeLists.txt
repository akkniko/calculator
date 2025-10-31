cmake_minimum_required(VERSION 3.15)
project(CalculatorApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mycalc
    app/main.cpp
    app/core/ExpressionParser.cpp
    app/core/ExpressionEvaluator.cpp
    app/core/FunctionRegistry.cpp
    app/system/PluginLoader.cpp
)

target_include_directories(mycalc PRIVATE
    app/core
    app/system
    include
)

set_target_properties(mycalc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
)

add_subdirectory(extensions)

if (WIN32)
    target_link_libraries(mycalc PRIVATE ws2_32)
endif()
