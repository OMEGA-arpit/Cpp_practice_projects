#include "InputHandler.h"
#include <iostream>

void InputHandler::removeLeadingAndTrailingWhitespaces(std::string& input) {
    size_t first = input.find_first_not_of(Constants::WHITESPACE_CHARS);
    size_t last  = input.find_last_not_of(Constants::WHITESPACE_CHARS);

    if (first == std::string::npos)
    {
        input = Constants::EMPTY_STRING;
    }
    else
    {
        input = input.substr(first, (last - first + 1));
    }
}

void InputHandler::inputString(std::string& input) {
    while (true) 
    {
        std::getline(std::cin, input);
        removeLeadingAndTrailingWhitespaces(input);
        if (input == Constants::EMPTY_STRING)
        {
            logger->printMessage(Constants::MSG_EMPTY_INPUT);
        }
        else
        {
            break;
        }
    }
}
