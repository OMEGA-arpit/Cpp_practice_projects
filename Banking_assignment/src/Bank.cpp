#include "Bank.h"
#include "Messages.h"
#include "InputHandler.h"
#include "Constants.h"
#include "Display.h"

Bank::Bank() {
    // Instantiation order is important: CustomerController must exist before
    // AdminController (which stores a raw pointer to it), and both controllers
    // must exist before the login handlers reference them.
    customerController = std::make_unique<CustomerController>();
    adminController    = std::make_unique<AdminController>(&customerService, customerController.get());
    adminLoginHandler  = std::make_shared<AdminLoginHandler>(admin, adminController.get());
    customerLoginHandler = std::make_shared<CustomerLoginHandler>(customerService, customerController.get());
}

// Non-owning constructor used for dependency injection (primarily in tests).
// The lambda [](ILoginHandler*){} is a no-op deleter: the shared_ptr will not
// attempt to destroy the externally-owned handler when Bank goes out of scope.
Bank::Bank(ILoginHandler* adminHandler, ILoginHandler* customerHandler)
    : adminLoginHandler{adminHandler, [](ILoginHandler*){}}
    , customerLoginHandler{customerHandler, [](ILoginHandler*){}} {}

bool Bank::login(Constants::UserRole role) {
    int attempts = 0;
    bool isSuccessful = false;

    ILoginHandler* handler = (role == Constants::UserRole::ADMIN)
                            ? adminLoginHandler.get()
                            : customerLoginHandler.get();

    while (!isSuccessful && attempts < Constants::MAX_LOGIN_ATTEMPTS)
    {
        Constants::LoginResult loginResult = handler->login();

        // ACCOUNT_NOT_FOUND is not a credential failure — the user supplied
        // a non-existent account number. Treat it as a graceful no-op: stop
        // the retry loop and return true so the main menu is shown again.
        if (loginResult == Constants::LoginResult::ACCOUNT_NOT_FOUND)
        {
            isSuccessful = true;
            break;
        }

        if (loginResult == Constants::LoginResult::SUCCESS)
        {
            isSuccessful = true;
        }
        else
        {
            // Count only genuine credential failures.
            attempts++;
            if (attempts < Constants::MAX_LOGIN_ATTEMPTS)
            {
                Display::printMessage(Messages::MSG_LOGIN_FAILED);
                Display::printWithNumber(Messages::MSG_LEFT_ATTEMPTS, Constants::MAX_LOGIN_ATTEMPTS - attempts);
            }
        }
    }

    if (!isSuccessful && attempts >= Constants::MAX_LOGIN_ATTEMPTS)
    {
        Display::printMessage(Messages::MSG_ACCESS_DENIED);
    }

    return isSuccessful;
}

bool Bank::handleChoice(int choice) {
    bool continueProgram = true;
    bool validChoice = true;
    Constants::UserRole role = Constants::UserRole::CUSTOMER;

    switch (choice)
    {
        case 1:
            role = Constants::UserRole::ADMIN;
            break;

        case 2:
            role = Constants::UserRole::CUSTOMER;
            break;

        case 3:
            continueProgram = false;
            break;

        default:
            Display::printMessage(Messages::MSG_INVALID_CHOICE);
            validChoice = false;
    }

    if (continueProgram && validChoice)
    {
        if (!login(role))
        {
            continueProgram = false;
        }
    }

    return continueProgram;
}

void Bank::handleMenu() {
    int choice;

    while (true)
    {
        Display::printMessage(Messages::MSG_BANK_MENU);
        Display::printMessage(Messages::MSG_INPUT_CHOICE);

        InputHandler::inputValue(choice);
        if (!handleChoice(choice))
        {
            Display::printMessage(Messages::MSG_PROGRAM_EXIT);
            return;
        }
    }
}
