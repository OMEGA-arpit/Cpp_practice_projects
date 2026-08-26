#include "AdminController.h"
#include "Messages.h"
#include "InputHandler.h"
#include "Customer.h"
#include "Display.h"
#include "Constants.h"
#include "CustomerController.h"
#include <iostream>
#include <iomanip>

void AdminController::registerCustomer() {
    Display::printMessage(Messages::MSG_REGISTER_CUSTOMER);

    std::string name, phone, email;

    Display::printMessage(Messages::MSG_CUSTOMER_NAME);
    InputHandler::inputString(name, Constants::InputType::NAME);

    Display::printMessage(Messages::MSG_CUSTOMER_EMAIL);
    InputHandler::inputString(email, Constants::InputType::EMAIL);

    Display::printMessage(Messages::MSG_CUSTOMER_PHONE);
    InputHandler::inputString(phone, Constants::InputType::PHONE);

    auto result = customerService->createCustomer(name, email, phone);
    Display::printWithValue(Messages::MSG_ACCOUNT_NUMBER, result.accountNumber);
    Display::printWithValue(Messages::MSG_PIN, result.pin);

    Display::printMessage(Messages::MSG_CUSTOMER_REGISTERED_SUCCESS);
}

void AdminController::displayCustomersInformation() {
    const auto& customers = customerService->getCustomers();

    if (customers.empty())
    {
        Display::printMessage(Messages::MSG_NO_CUSTOMERS_FOUND);
        return;
    }

    Display::printMessage(Messages::MSG_LIST_ALL_CUSTOMERS);
    Display::printWithNumber(Messages::MSG_TOTAL_CUSTOMERS, customers.size());

    for (const Customer& customer : customers)
    {
        customer.displayInformation();
        Display::printMessage(Messages::MSG_SEPARATOR);
    }
}

void AdminController::displayAccountsInformation() {
    const auto& customers = customerService->getCustomers();

    if (customers.empty())
    {
        Display::printMessage(Messages::MSG_NO_ACCOUNTS_FOUND);
        return;
    }

    Display::printMessage(Messages::MSG_LIST_ALL_ACCOUNTS);
    Display::printWithNumber(Messages::MSG_TOTAL_ACCOUNTS, customers.size());

    for (const Customer& customer : customers) {
        customer.displayAccountDetails();
        Display::printMessage(Messages::MSG_SEPARATOR);
    }
}

void AdminController::displayCustomerByAccountNumber() {
    Display::printMessage(Messages::MSG_SEARCH_CUSTOMER_HEADER);
    
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_NUMBER);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);
    
    Customer* customer = customerService->findCustomerByAccountNumber(accountNumber);
    
    if (customer) 
    {
        Display::printMessage(Messages::MSG_CUSTOMER_FOUND);
        customer->displayInformation();
    } 
    else 
    {
        Display::printWithValue(Messages::MSG_CUSTOMER_NOT_FOUND_WITH_ACCOUNT, accountNumber);
    }
}

void AdminController::displayAccountByNumber() {
    Display::printMessage(Messages::MSG_SEARCH_ACCOUNT_HEADER);
    
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_NUMBER);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);
    
    Customer* customer = customerService->findCustomerByAccountNumber(accountNumber);
    
    if (customer) 
    {
        Display::printMessage(Messages::MSG_ACCOUNT_FOUND);
        customer->displayAccountDetails();
    } 
    else 
    {
        Display::printWithValue(Messages::MSG_ACCOUNT_NOT_FOUND_WITH_NUMBER, accountNumber);
    }
}

void AdminController::updateCustomerName(Customer* customer) {
    std::string newValue;
    Display::printMessage(Messages::MSG_ENTER_NEW_NAME);
    InputHandler::inputString(newValue, Constants::InputType::NAME);
    customer->setName(newValue);
    Display::printMessage(Messages::MSG_NAME_UPDATED);
}

void AdminController::updateCustomerEmail(Customer* customer) {
    std::string newValue;
    Display::printMessage(Messages::MSG_ENTER_NEW_EMAIL);
    InputHandler::inputString(newValue, Constants::InputType::EMAIL);
    customer->setEmail(newValue);
    Display::printMessage(Messages::MSG_EMAIL_UPDATED);
}

void AdminController::updateCustomerPhone(Customer* customer) {
    std::string newValue;
    Display::printMessage(Messages::MSG_ENTER_NEW_PHONE);
    InputHandler::inputString(newValue, Constants::InputType::PHONE);
    customer->setPhone(newValue);
    Display::printMessage(Messages::MSG_PHONE_UPDATED);
}

void AdminController::updateCustomerPin(Customer* customer) {
    std::string newValue;
    Display::printMessage(Messages::MSG_ENTER_NEW_PIN);
    InputHandler::inputString(newValue, Constants::InputType::PIN);
    customer->getAccount().setPin(newValue);
    Display::printMessage(Messages::MSG_PIN_UPDATED);
}

bool AdminController::handleEditMenuChoice(int choice, Customer* customer) {
    bool isValidChoice = true;

    switch (choice) {
        case 1:
            updateCustomerName(customer);
            break;
            
        case 2:
            updateCustomerEmail(customer);
            break;
            
        case 3:
            updateCustomerPhone(customer);
            break;
            
        case 4:
            updateCustomerPin(customer);
            break;
            
        case 5:
            Display::printMessage(Messages::MSG_EDIT_CANCELLED);
            break;
            
        default:
            Display::printMessage(Messages::MSG_INVALID_CHOICE);
            isValidChoice = false;
    }

    return isValidChoice;
}

void AdminController::editCustomerDetails() {
    Display::printMessage(Messages::MSG_EDIT_CUSTOMER);
    
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_NUMBER);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);
    
    Customer* customer = customerService->findCustomerByAccountNumber(accountNumber);
    
    if (!customer) 
    {
        Display::printMessage(Messages::MSG_CUSTOMER_NOT_FOUND);
        return;
    }
    
    Display::printMessage(Messages::MSG_CURRENT_DETAILS);
    customer->displayInformation();
    Display::printMessage(Messages::MSG_EDIT_MENU);

    int choice;
    InputHandler::inputValue(choice);
    
    handleEditMenuChoice(choice, customer);
}

void AdminController::performAccountOperation(Customer* customer) {
    Display::printMessage(Messages::MSG_ACCOUNT_MANAGEMENT_MENU);
    
    int choice;
    InputHandler::inputValue(choice);
    
    switch (choice) {
        case 1:
            customerController->performDeposit(*customer); 
            break;
        case 2:
            customerController->performWithdrawal(*customer);
            break;
        case 3:
            Display::printWithAmount(Messages::MSG_CURRENT_BALANCE, 
                customer->getAccount().getBalance());
            break;
        case 4:
            Display::printMessage(Messages::MSG_OPERATION_CANCELLED);
            break;
        default:
            Display::printMessage(Messages::MSG_INVALID_CHOICE);
    }
}

void AdminController::manageCustomerAccount() {
    Display::printMessage(Messages::MSG_MANAGE_ACCOUNT_HEADER);
    
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_NUMBER);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);
    
    Customer* customer = customerService->findCustomerByAccountNumber(accountNumber);
    
    if (!customer) 
    {
        Display::printMessage(Messages::MSG_CUSTOMER_NOT_FOUND);
        return;
    }
    
    performAccountOperation(customer);
}

void AdminController::handleCustomerDeletion() {
    Display::printMessage(Messages::MSG_DELETE_CUSTOMER_HEADER);
    
    std::string accountNumber;
    Display::printMessage(Messages::MSG_ENTER_ACCOUNT_TO_DELETE);
    InputHandler::inputString(accountNumber, Constants::InputType::ACCOUNT_NUMBER);
    
    Customer* customer = customerService->findCustomerByAccountNumber(accountNumber);
    
    if (!customer) 
    {
        Display::printMessage(Messages::MSG_CUSTOMER_NOT_FOUND);
    }
    else
    {
        if (!customerService->deleteCustomerFromBank(accountNumber)) 
        {
            Display::printWithAmount(Messages::MSG_CANNOT_DELETE_WITH_BALANCE, 
            customer->getAccount().getBalance());
            Display::printMessage(Messages::MSG_WITHDRAW_FUNDS_FIRST);
        }
        else
        {
            Display::printMessage(Messages::MSG_CUSTOMER_DELETED_SUCCESS);
        }
    }
}

bool AdminController::handleMenuChoice(int choice) {
    bool continueProgram = true;

    switch (choice)
    {
        case 1:
        registerCustomer();
        break;

        case 2:
        displayCustomersInformation();
        break;

        case 3:
        displayAccountsInformation();
        break;

        case 4:
        displayCustomerByAccountNumber();
        break;

        case 5:
        displayAccountByNumber();
        break;

        case 6:
        editCustomerDetails();
        break;

        case 7:
        manageCustomerAccount();
        break;

        case 8:
        handleCustomerDeletion();
        break;

        case 9:
        continueProgram = false;
        break;

        default:
        Display::printMessage(Messages::MSG_INVALID_CHOICE);
    }
    
    return continueProgram;
}

bool AdminController::handleMenu() {
    int choice;
    bool continueProgram = true;

    while (continueProgram)
    {
        Display::printMessage(Messages::MSG_ADMIN_OPERATIONS_MENU);
        Display::printMessage(Messages::MSG_INPUT_CHOICE);

        InputHandler::inputValue(choice);
        continueProgram = handleMenuChoice(choice);
    }

    return continueProgram;
}
