#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file Constants.h
 * @brief Application-wide numeric constants, character literals, and enumerations.
 *
 * All values are defined as @c inline @c constexpr (or @c inline @c const for strings)
 * so they have external linkage and produce no out-of-line storage.
 * Adjust these values to reconfigure application-wide limits without touching
 * business logic.
 */

#include <string>

namespace Constants {

    enum class UserRole {
        ADMIN,
        CUSTOMER
    };

    enum class TransactionType {
        DEPOSIT,
        WITHDRAWAL
    };

    enum InputType {
        NAME,
        EMAIL,
        PHONE,
        ACCOUNT_NUMBER,
        PIN,
        USERNAME,
        PASSWORD
    };

    enum class LoginResult {
        SUCCESS,
        FAILED,
        ACCOUNT_NOT_FOUND
    };

    inline constexpr long INITIAL_TRANSACTION_ID = 1;
    inline constexpr long INITIAL_ACCOUNT_NUMBER = 10000000;

    inline constexpr int PIN_LENGTH = 4;
    inline constexpr int MIN_PIN_VALUE = 1000;
    inline constexpr int MAX_PIN_VALUE = 9999;

    inline constexpr int ACCOUNT_NUMBER_LENGTH = 8;
    inline constexpr int PHONE_LENGTH = 10;
    inline constexpr int MAX_LOGIN_ATTEMPTS = 3;
    inline constexpr int MIN_NAME_LENGTH = 3;
    inline constexpr int MIN_PASSWORD_LENGTH = 6;
    inline constexpr int MIN_USERNAME_LENGTH = 4;
    inline constexpr int MINI_STATEMENT_MAX_TRANSACTIONS = 5;

    inline constexpr int MIN_TRANSACTION_AMOUNT = 100;
    inline constexpr int MAX_TRANSACTION_AMOUNT = 10000;

    inline constexpr int ID_WIDTH = 5;
    inline constexpr int TYPE_WIDTH = 12;
    inline constexpr int AMOUNT_WIDTH = 10;
    inline constexpr int POSTBALANCE_WIDTH = 15;
    inline constexpr int DECIMAL_PRECISION = 2;

    inline constexpr char NEW_LINE = '\n';
    inline constexpr char AT_THE_RATE = '@';
    inline constexpr char FULL_STOP = '.';
    inline constexpr char WHITESPACE = ' ';
    inline constexpr char HYPHEN = '-';
    inline constexpr char TAB = '\t';

    inline const std::string EMPTY_STRING = "";
    inline const std::string ADMIN_NAME = "Hiya";
    inline const std::string ADMIN_USERNAME = "hiya";
    inline const std::string ADMIN_PASSWORD = "system"; 
    inline const std::string WHITESPACE_CHARS = " \t\n\r";
};

#endif
