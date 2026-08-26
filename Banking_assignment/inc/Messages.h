#ifndef MESSAGES_H
#define MESSAGES_H

/**
 * @file Messages.h
 * @brief All user-facing string literals displayed by the application.
 *
 * Centralising strings here keeps controllers and domain objects free of
 * hardcoded text and makes UI copy changes a single-file edit.
 * Strings are grouped by the component that uses them.
 */

#include <string>

namespace Messages {

    //InputHandler
    inline const std::string MSG_INVALID_NUMBER = "Invalid Input. Please enter a number: ";
    inline const std::string MSG_INVALID_INTEGER = "Invalid Input. Please enter an integer: ";
    inline const std::string MSG_OUT_OF_RANGE = "Invalid Value. Please enter an integer in range: ";
    inline const std::string MSG_EMPTY_INPUT = "Input cannot be empty! Enter again: ";
    inline const std::string MSG_ENTER_AGAIN = "Enter again: ";

    //Validator
    inline const std::string MSG_INVALID_DIGITS = "Invalid Input. Only digits expected!\n";
    inline const std::string MSG_INVALID_LENGTH = "Invalid Input. Input should be exactly ";
    inline const std::string MSG_DIGITS_SUFFIX = " digits!\n";
    inline const std::string MSG_INVALID_NAME_LENGTH = "Invalid Input. Name should be at least ";
    inline const std::string MSG_INVALID_USERNAME_LENGTH = "Invalid Input. UserName should be at least ";
    inline const std::string MSG_CHARACTERS_SUFFIX = " characters!\n";
    inline const std::string MSG_INVALID_NAME_CHARS = "Invalid Input. Only alphabets and spaces expected!\n";
    inline const std::string MSG_EMAIL_NO_AT = "Email must contain '@'.\n";
    inline const std::string MSG_EMAIL_NO_DOMAIN = "Email must have a domain (e.g., @gmail.com).\n";
    inline const std::string MSG_EMAIL_MULTIPLE_AT = "Email cannot contain multiple '@' symbols.\n";
    inline const std::string MSG_EMAIL_CONSECUTIVE_DOTS = "Email cannot contain consecutive dots.\n";
    inline const std::string MSG_INVALID_PASSWORD_LENGTH = "Invalid Input. Password should be at least ";

    //Bank
    inline const std::string MSG_BANK_MENU =
    "\n=============== WELCOME ===============\n"
    "1. Login as an Admin\n"
    "2. Login as a Customer\n"
    "3. Exit\n"
    "========================================\n";
    inline const std::string MSG_ADMIN_LOGIN = "\n===== ADMIN LOGIN =====\n";
    inline const std::string MSG_CUSTOMER_LOGIN = "\n===== CUSTOMER LOGIN =====\n";
    inline const std::string MSG_ENTER_USERNAME = "Enter username: ";
    inline const std::string MSG_ENTER_PASSWORD = "Enter password: ";
    inline const std::string MSG_ENTER_ACCOUNT_NUMBER = "Enter account number: ";
    inline const std::string MSG_ACCOUNT_DOES_NOT_EXIST = "This account number does not exist. Please visit your nearest branch to open a new account.\n";
    inline const std::string MSG_ENTER_ACCOUNT_PIN = "Enter PIN: ";
    inline const std::string MSG_LOGIN_SUCCESS = "\nLogin successful!\n";
    inline const std::string MSG_LOGIN_FAILED = "\nLogin failed! Incorrect credentials.";
    inline const std::string MSG_ACCESS_DENIED = "\nAccess denied! Maximum login attempts exceeded.\n";
    inline const std::string MSG_LEFT_ATTEMPTS = "\nAttempts remaining: ";
    inline const std::string MSG_ACCOUNT_NUMBER = "\nAccount Number: ";
    inline const std::string MSG_PIN = "PIN: ";

    //AdminController
    inline const std::string MSG_ADMIN_OPERATIONS_MENU =
    "\n=============== ADMIN OPERATIONS ===============\n"
    "1. Register Customer\n"
    "2. View All Customers\n"
    "3. View All Accounts\n"
    "4. Display Customer via Account Number\n"
    "5. Display Account via Account Number\n"
    "6. Edit Customer Details\n"
    "7. Manage Customer Account\n"
    "8. Delete Customer\n"
    "9. Logout\n"
    "================================================\n";

    inline const std::string MSG_REGISTER_CUSTOMER = "\n===== REGISTER NEW CUSTOMER =====\n";
    inline const std::string MSG_CUSTOMER_NAME = "Customer Name: ";
    inline const std::string MSG_CUSTOMER_EMAIL = "Customer Email: ";
    inline const std::string MSG_CUSTOMER_PHONE = "Customer Phone Number: ";
    inline const std::string MSG_CUSTOMER_REGISTERED_SUCCESS = "\nCustomer registered successfully!\n";

    inline const std::string MSG_NO_CUSTOMERS_FOUND = "\nNo customers found.\n";
    inline const std::string MSG_LIST_ALL_CUSTOMERS = "\n===== LIST OF ALL CUSTOMERS =====\n";
    inline const std::string MSG_TOTAL_CUSTOMERS = "Total Customers: ";
    inline const std::string MSG_NO_ACCOUNTS_FOUND = "\nNo accounts found.\n";
    inline const std::string MSG_LIST_ALL_ACCOUNTS = "\n===== LIST OF ALL ACCOUNTS =====\n";
    inline const std::string MSG_TOTAL_ACCOUNTS = "Total Accounts: ";
    inline const std::string MSG_SEPARATOR = "----------------------------\n";

    inline const std::string MSG_SEARCH_CUSTOMER_HEADER = "\n===== SEARCH CUSTOMER BY ACCOUNT =====\n";
    inline const std::string MSG_CUSTOMER_FOUND = "\nCustomer Found!\n";
    inline const std::string MSG_CUSTOMER_NOT_FOUND_WITH_ACCOUNT = "\nNo customer found with account number: ";

    inline const std::string MSG_SEARCH_ACCOUNT_HEADER = "\n===== SEARCH ACCOUNT BY NUMBER =====\n";
    inline const std::string MSG_ACCOUNT_FOUND = "\nAccount Found!\n";
    inline const std::string MSG_ACCOUNT_NOT_FOUND_WITH_NUMBER = "\nNo account found with account number: ";

    inline const std::string MSG_EDIT_CUSTOMER = "\n===== EDIT CUSTOMER DETAILS =====\n";
    inline const std::string MSG_CURRENT_DETAILS = "\nCurrent Details:\n";
    inline const std::string MSG_EDIT_MENU =
        "\n--- What would you like to edit? ---\n"
        "1. Name\n"
        "2. Email\n"
        "3. Phone\n"
        "4. PIN\n"
        "5. Cancel\n"
        "Enter choice: ";

    inline const std::string MSG_ENTER_NEW_NAME = "Enter new name: ";
    inline const std::string MSG_ENTER_NEW_EMAIL = "Enter new email: ";
    inline const std::string MSG_ENTER_NEW_PHONE = "Enter new phone: ";
    inline const std::string MSG_ENTER_NEW_PIN = "Enter new PIN (4 digits): ";
    inline const std::string MSG_NAME_UPDATED = "Name updated!\n";
    inline const std::string MSG_EMAIL_UPDATED = "Email updated!\n";
    inline const std::string MSG_PHONE_UPDATED = "Phone updated!\n";
    inline const std::string MSG_PIN_UPDATED = "PIN updated!\n";
    inline const std::string MSG_EDIT_CANCELLED = "Edit cancelled.\n";
    inline const std::string MSG_CUSTOMER_NOT_FOUND = "\nCustomer not found!\n";

    inline const std::string MSG_MANAGE_ACCOUNT_HEADER = "\n===== MANAGE CUSTOMER ACCOUNT =====\n";
    inline const std::string MSG_ACCOUNT_MANAGEMENT_MENU =
        "\n1. Deposit\n"
        "2. Withdraw\n"
        "3. Check Balance\n"
        "4. Cancel\n"
        "Enter choice: ";
    inline const std::string MSG_OPERATION_CANCELLED = "\nOperation cancelled.\n";

    inline const std::string MSG_DELETE_CUSTOMER_HEADER = "\n===== DELETE CUSTOMER =====\n";
    inline const std::string MSG_ENTER_ACCOUNT_TO_DELETE = "Enter Account Number of customer to delete: ";
    inline const std::string MSG_CANNOT_DELETE_WITH_BALANCE = "\nCannot delete customer with remaining balance: ";
    inline const std::string MSG_WITHDRAW_FUNDS_FIRST = "Please withdraw all funds before deletion.\n";
    inline const std::string MSG_CUSTOMER_DELETED_SUCCESS = "Customer Deleted Successfully!\n";

    inline const std::string MSG_LOGOUT = "\nLogged out successfully!\n";

    //CustomerController
    inline const std::string MSG_CUSTOMER_OPERATIONS_MENU =
    "\n=============== CUSTOMER OPERATIONS ===============\n"
    "1. Deposit\n"
    "2. Withdraw\n"
    "3. Check Balance\n"
    "4. Change Pin\n"
    "5. Mini Statement\n"
    "6. Bank Statement\n"
    "7. Logout\n"
    "====================================================\n";
    inline const std::string MSG_DEPOSIT_FAILED = "Deposit failed. Entered amount is not in range.\n";
    inline const std::string MSG_WITHDRAWAL_FAILED = "Withdrawal failed. Entered amount is not in range.\n";
    inline const std::string MSG_TRANSACTION_RANGE = "Transaction amount must be between ";
    inline const std::string MSG_ENTER_DEPOSIT_AMOUNT = "Enter the amount you want to deposit: ";
    inline const std::string MSG_DEPOSIT_SUCCESS = "\nDeposited Money! Balance after transaction: ";
    inline const std::string MSG_ENTER_WITHDRAWAL_AMOUNT = "Enter the amount you want to withdraw: ";
    inline const std::string MSG_WITHDRAWAL_SUCCESS = "\nWithdrawn Money! Balance after transaction: ";
    inline const std::string MSG_INSUFFICIENT_BALANCE = "You do not have enough balance for this!\n";

    inline const std::string MSG_CURRENT_BALANCE = "Your current balance is: ";

    inline const std::string MSG_MINI_STATEMENT_HEADER = "\n========== Mini Statement (Last 5 Transactions) ==========\n";
    inline const std::string MSG_BANK_STATEMENT_HEADER = "\n================== Full Bank Statement ===================\n";
    inline const std::string MSG_STATEMENT_FOOTER = "===========================================================\n";
    inline const std::string MSG_TRANSACTION_TYPE_DEPOSIT = "Deposit";
    inline const std::string MSG_TRANSACTION_TYPE_WITHDRAWAL = "Withdrawal";

    inline const std::string MSG_ENTER_OLD_PIN = "Enter old PIN: ";
    inline const std::string MSG_ENTER_NEW_PIN_CHANGE = "Enter new PIN (4 digits): ";
    inline const std::string MSG_REENTER_PIN = "Re-enter your PIN: ";
    inline const std::string MSG_PIN_UPDATED_SUCCESS = "PIN updated!.\n";
    inline const std::string MSG_LOGGING_OUT = "You are getting logged out. Kindly login again!\n";
    inline const std::string MSG_PINS_DO_NOT_MATCH = "PINS do not match. Try again!\n";
    inline const std::string MSG_INCORRECT_PIN = "Entered PIN is incorrect.\n";
    inline const std::string MSG_FORGOT_PIN_CONTACT = "If you have forgot the pin, kindly contact your bank\n";

    inline const std::string MSG_NO_TRANSACTIONS = "\nNo transactions found.\n";

    inline const std::string MSG_INPUT_CHOICE = "\nEnter your choice: ";
    inline const std::string MSG_INVALID_CHOICE = "Invalid Choice! Please choose an option from menu.\n";
    inline const std::string MSG_PROGRAM_EXIT = "\nThank you for banking with us!\n";

    //Customer
    inline const std::string MSG_DISPLAY_CUSTOMER_NAME = "\nCustomer Name: ";
    inline const std::string MSG_DISPLAY_EMAIL = "Email: ";
    inline const std::string MSG_DISPLAY_PHONE = "Phone: ";
    inline const std::string MSG_DISPLAY_ACCOUNT_NUMBER = "\nAccount Number: ";
    inline const std::string MSG_DISPLAY_BALANCE = "Balance: ";

    //Admin
    inline const std::string MSG_DISPLAY_ADMIN_NAME = "\nAdmin Name: ";
    inline const std::string MSG_DISPLAY_USERNAME = "Username: ";

    // Transaction headers
    inline const std::string MSG_TRANSACTION_HEADER_ID = "ID";
    inline const std::string MSG_TRANSACTION_HEADER_TYPE = "Type";
    inline const std::string MSG_TRANSACTION_HEADER_AMOUNT = "Amount";
    inline const std::string MSG_TRANSACTION_HEADER_POSTBAL = "Post Balance";

};

#endif
