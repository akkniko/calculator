#ifndef DLL_MODEL_H
#define DLL_MODEL_H

#if defined(MYLIBRARY)
    #define LIBRARY_EXPORT __declspec(dllexport)
#else
    #define LIBRARY_EXPORT
#endif

#include <stdexcept>
#include "dllData.h"

// Контракт между DLL и калькулятором
extern "C" LIBRARY_EXPORT Data getData() noexcept;
extern "C" LIBRARY_EXPORT void doCalculation(StackT& stack);

#endif // DLL_MODEL_H
