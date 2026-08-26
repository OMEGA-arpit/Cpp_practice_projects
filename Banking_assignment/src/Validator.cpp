#include "Validator.h"
#include "Constants.h"
#include "Messages.h"
#include <climits>
#include <iostream>
#include <limits>
#include <cctype>

ValidationResult Validator::isValidDigitsOnly(const std::string& input, size_t expectedLength) {
    if (input.size() != expectedLength)
    {
        return ValidationResult::fail(
            Messages::MSG_INVALID_LENGTH + std::to_string(expectedLength) + Messages::MSG_DIGITS_SUFFIX);
    }

    for (char character : input)
    {
        if (!std::isdigit(static_cast<unsigned char>(character)))
        {
            return ValidationResult::fail(Messages::MSG_INVALID_DIGITS);
        }
    }

    return ValidationResult::ok();
}

ValidationResult Validator::isValidName(const std::string& input) {
    if (input.size() < Constants::MIN_NAME_LENGTH)
    {
        return ValidationResult::fail(
            Messages::MSG_INVALID_NAME_LENGTH + std::to_string(Constants::MIN_NAME_LENGTH) + Messages::MSG_CHARACTERS_SUFFIX);
    }

    for (char character : input)
    {
        if (!std::isalpha(static_cast<unsigned char>(character)) && character != ' ')
        {
            return ValidationResult::fail(Messages::MSG_INVALID_NAME_CHARS);
        }
    }

    return ValidationResult::ok();
}

// Email validation applies four lightweight structural rules in order:
//  1. Exactly one '@' must be present.
//  2. There must be a '.' after the '@' that is not the final character
//     (ensures a non-empty domain extension, e.g. ".com").
//  3. No two consecutive '.' characters may appear after the '@'.
// This intentionally performs only a basic sanity check, not full
// RFC 5321/5322 compliance, which is out of scope for this application.
ValidationResult Validator::isValidEmail(const std::string& email) {
    size_t atPosition = email.find(Constants::AT_THE_RATE);

    if (atPosition == std::string::npos)
    {
        return ValidationResult::fail(Messages::MSG_EMAIL_NO_AT);
    }
    if (email.find(Constants::AT_THE_RATE, atPosition + 1) != std::string::npos)
    {
        return ValidationResult::fail(Messages::MSG_EMAIL_MULTIPLE_AT);
    }

    size_t dotPosition = email.find(Constants::FULL_STOP, atPosition);
    if (dotPosition == std::string::npos || dotPosition == email.length() - 1)
    {
        return ValidationResult::fail(Messages::MSG_EMAIL_NO_DOMAIN);
    }
    if (email.find(Constants::FULL_STOP, dotPosition + 1) == dotPosition + 1)
    {
        return ValidationResult::fail(Messages::MSG_EMAIL_CONSECUTIVE_DOTS);
    }

    return ValidationResult::ok();
}

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

ValidationResult Validator::isValidInput(const std::string& input, Constants::InputType type) {
    switch (type) {
        case Constants::InputType::NAME:
            return isValidName(input);

        case Constants::InputType::EMAIL:
            return isValidEmail(input);

        case Constants::InputType::PHONE:
            return isValidDigitsOnly(input, Constants::PHONE_LENGTH);

        case Constants::InputType::ACCOUNT_NUMBER:
            return isValidDigitsOnly(input, Constants::ACCOUNT_NUMBER_LENGTH);

        case Constants::InputType::PIN:
            return isValidDigitsOnly(input, Constants::PIN_LENGTH);

        case Constants::InputType::PASSWORD:
            if (input.size() < Constants::MIN_PASSWORD_LENGTH)
            {
                return ValidationResult::fail(
                    Messages::MSG_INVALID_PASSWORD_LENGTH + std::to_string(Constants::MIN_PASSWORD_LENGTH) + Messages::MSG_CHARACTERS_SUFFIX);
            }
            return ValidationResult::ok();

        case Constants::InputType::USERNAME:
            if (input.size() < Constants::MIN_USERNAME_LENGTH)
            {
                return ValidationResult::fail(
                    Messages::MSG_INVALID_USERNAME_LENGTH + std::to_string(Constants::MIN_USERNAME_LENGTH) + Messages::MSG_CHARACTERS_SUFFIX);
            }
            return ValidationResult::ok();

        default:
            return ValidationResult::ok();
    }
}

