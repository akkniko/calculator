cmake_minimum_required(VERSION 3.15)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (CMAKE_CONFIGURATION_TYPES)
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/plugins)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/plugins)
    endforeach()
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
endif()

function(add_plugin plugin_name source_file)
    add_library(${plugin_name} SHARED ${source_file})
    target_include_directories(${plugin_name} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_compile_definitions(${plugin_name} PRIVATE MYLIBRARY)
    set_target_properties(${plugin_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    )
endfunction()

# Автопоиск всех подпапок с спп файлами
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(subdir ${SUBDIRS})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/*.cpp")
        foreach(f ${CPP_FILES})
            get_filename_component(fname ${f} NAME_WE)
            add_plugin(${fname} ${f})
        endforeach()
    endif()
endforeach()
