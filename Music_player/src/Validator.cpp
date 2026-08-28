#include "Validator.h"
#include <iostream>
#include <limits>

bool Validator::isInputStreamValid() {
    bool isValidStream = false;
    if (std::cin.fail()) 
    {
        std::cin.clear();
    }
    else
    {
        while (std::cin.peek() == Constants::WHITESPACE || std::cin.peek() == Constants::TAB) 
        {
            std::cin.get();
        }
    
        if (std::cin.peek() == '\n') 
        {
            isValidStream = true;
        }
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), Constants::NEW_LINE);
    return isValidStream;
}
