#include "CustomerLoginHandler.h"
#include "Display.h"
#include "Messages.h"
#include "InputHandler.h"

Customer* CustomerLoginHandler::getCustomer() {
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_NUMBER);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);

    Customer* customer = customerService.findCustomerByAccountNumber(accountNumber);
    if (!customer)
    {
        Display::printMessage(Messages::MSG_ACCOUNT_DOES_NOT_EXIST);
    }
    return customer;
}

bool CustomerLoginHandler::verifyPin(Customer* customer) {
    std::string pin;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_PIN);
    InputHandler::inputString(pin, Constants::InputType::PIN);

    return customer->authenticate(customer->getAccount().getAccountNumber(), pin);
}

Constants::LoginResult CustomerLoginHandler::login() {
    Constants::LoginResult result = Constants::LoginResult::FAILED;

    Display::printMessage(Messages::MSG_CUSTOMER_LOGIN);

    Customer* customer = getCustomer();
    if (!customer)
    {
        result = Constants::LoginResult::ACCOUNT_NOT_FOUND;
    }
    else if (verifyPin(customer))
    {
        result = Constants::LoginResult::SUCCESS;
        Display::printMessage(Messages::MSG_LOGIN_SUCCESS);
        if (!customerController->handleMenu(*customer))
        {
            logout();
        }
    }

    return result;
}

void CustomerLoginHandler::logout() {
    Display::clearScreen();
    Display::printMessage(Messages::MSG_LOGOUT);
}
