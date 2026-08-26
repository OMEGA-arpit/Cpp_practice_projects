#include "InputHandler.h"
#include "Constants.h"
#include "Messages.h"
#include "Validator.h"
#include "Display.h"
#include <iostream>

void InputHandler::inputValue(double& value) {
    while (true)
    {
        std::cin >> value;
        if (!Validator::isInputStreamValid())
        {
            Display::printMessage(Messages::MSG_INVALID_NUMBER);
        }
        else
        {
            break;
        }
    }
}

void InputHandler::inputValue(int& value) {
    while (true)
    {
        std::cin >> value;
        if (!Validator::isInputStreamValid())
        {
            Display::printMessage(Messages::MSG_INVALID_INTEGER);
        }
        else
        {
            break;
        }
    }
}

void InputHandler::removeLeadingAndTrailingWhitespaces(std::string& input) {
    size_t first = input.find_first_not_of(Constants::WHITESPACE_CHARS);
    size_t last  = input.find_last_not_of(Constants::WHITESPACE_CHARS);

    if (first == std::string::npos)
    {
        input.clear();
    }
    else
    {
        input = input.substr(first, (last - first + 1));
    }
}

void InputHandler::inputString(std::string& input, Constants::InputType type) {
    while (true)
    {
        std::getline(std::cin, input);
        removeLeadingAndTrailingWhitespaces(input);

        if (input.empty())
        {
            Display::printMessage(Messages::MSG_EMPTY_INPUT);
        }
        else if (auto result = Validator::isValidInput(input, type); !result)
        {
            Display::printMessage(result.errorMessage);
            Display::printMessage(Messages::MSG_ENTER_AGAIN);
        }
        else
        {
            break;
        }
    }
}

