#ifndef DLL_DATA_H
#define DLL_DATA_H

#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>

struct Data {
    std::string value;    
    unsigned char priority; 
    bool isUnary;        
};

using StackT = std::stack<double>;

#endif // DLL_DATA_H
