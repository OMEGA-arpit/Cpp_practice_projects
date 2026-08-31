#include "CustomerController.h"
#include "Constants.h"
#include "Display.h"
#include "InputHandler.h"
#include "Messages.h"
#include <iomanip>

void CustomerController::performDeposit(Customer& customer) {
    double amount;
    Display::printTransactionRange();
    Display::printMessage(Messages::MSG_ENTER_DEPOSIT_AMOUNT);
    InputHandler::inputValue(amount);
    if (customer.getAccount().deposit(amount)) 
    {
        Display::printWithAmount(Messages::MSG_DEPOSIT_SUCCESS, 
                                customer.getAccount().getBalance());
    } 
    else 
    {
        Display::printMessage(Messages::MSG_DEPOSIT_FAILED);
    }
}

void CustomerController::performWithdrawal(Customer& customer) {
    double amount;
    Display::printTransactionRange();
    Display::printMessage(Messages::MSG_ENTER_WITHDRAWAL_AMOUNT);
    InputHandler::inputValue(amount);

    if (customer.getAccount().withdrawal(amount)) 
    {
        Display::printWithAmount(Messages::MSG_WITHDRAWAL_SUCCESS, 
        customer.getAccount().getBalance());
    } 
    else 
    {
        if (customer.getAccount().getBalance() < amount)
        {
            Display::printMessage(Messages::MSG_INSUFFICIENT_BALANCE);
        }
        else
        {
            Display::printMessage(Messages::MSG_WITHDRAWAL_FAILED);
        }
    }
}

bool CustomerController::isOldPinCorrect(Account& account) {
    std::string pin;
    Display::printMessage(Messages::MSG_ENTER_OLD_PIN);
    InputHandler::inputString(pin, Constants::InputType::PIN);

    bool isCorrect = account.verifyPin(pin);

    if (!isCorrect)
    {
        Display::printMessage(Messages::MSG_INCORRECT_PIN);
        Display::printMessage(Messages::MSG_FORGOT_PIN_CONTACT);
    }

    return isCorrect; 
}

bool CustomerController::changePin(Customer& customer) {
    bool continueProgram = true;

    if (isOldPinCorrect(customer.getAccount()))
    {
        std::string newPin, confirmPin;
        Display::printMessage(Messages::MSG_ENTER_NEW_PIN_CHANGE);
        InputHandler::inputString(newPin, Constants::InputType::PIN);

        Display::printMessage(Messages::MSG_REENTER_PIN);
        InputHandler::inputString(confirmPin, Constants::InputType::PIN);

        if (newPin == confirmPin)
        {
            customer.getAccount().setPin(newPin);
            Display::printMessage(Messages::MSG_PIN_UPDATED_SUCCESS);
            Display::printMessage(Messages::MSG_LOGGING_OUT);
            continueProgram = false; 
        }
        else
        {
            Display::printMessage(Messages::MSG_PINS_DO_NOT_MATCH);
        }
    }

    return continueProgram; 
}

void CustomerController::displayMiniStatement(Customer& customer) {
    std::vector<Transaction> transactions = 
        customer.getAccount().getLastTransactions(Constants::MINI_STATEMENT_MAX_TRANSACTIONS);

    if (transactions.empty()) 
    {
        Display::printMessage(Messages::MSG_NO_TRANSACTIONS);
        return;
    }

    Display::printMessage(Messages::MSG_MINI_STATEMENT_HEADER);
    Display::printTransactionHeader();

    for (Transaction& transaction : transactions) 
    {
        std::string type = (transaction.getType() == Constants::TransactionType::DEPOSIT) 
        ? Messages::MSG_TRANSACTION_TYPE_DEPOSIT : Messages::MSG_TRANSACTION_TYPE_WITHDRAWAL;
        
        Display::printTransactionRow(transaction.getId(), type, 
                                     transaction.getAmount(), transaction.getPostBalance());
    }

    Display::printMessage(Messages::MSG_STATEMENT_FOOTER);
}

void CustomerController::displayBankStatement(Customer& customer) {
    const auto& transactions = customer.getAccount().getTransactions();

    if (transactions.empty()) 
    {
        Display::printMessage(Messages::MSG_NO_TRANSACTIONS);
        return;
    }

    Display::printMessage(Messages::MSG_BANK_STATEMENT_HEADER);
    Display::printTransactionHeader();

    for (const Transaction& transaction : transactions) 
    {
        std::string type = (transaction.getType() == Constants::TransactionType::DEPOSIT) 
                          ? Messages::MSG_TRANSACTION_TYPE_DEPOSIT 
                          : Messages::MSG_TRANSACTION_TYPE_WITHDRAWAL;
        
        Display::printTransactionRow(transaction.getId(), type, 
                                     transaction.getAmount(), 
                                     transaction.getPostBalance());
    }

    Display::printMessage(Messages::MSG_STATEMENT_FOOTER);
}

bool CustomerController::handleChoice(int choice, Customer& customer) {
    bool continueProgram = true;

    switch (choice)
    {
        case 1:
            performDeposit(customer);
            break;

        case 2:
            performWithdrawal(customer);
            break;

        case 3:
            Display::printWithAmount(Messages::MSG_CURRENT_BALANCE, customer.getAccount().getBalance());
            break;

        case 4:
        {
            continueProgram = changePin(customer);
            break;
        }    

        case 5:
            displayMiniStatement(customer);
            break;

        case 6:
            displayBankStatement(customer);
            break;

        case 7:
            continueProgram = false;
            break;

        default:
            Display::printMessage(Messages::MSG_INVALID_CHOICE);
    }
    
    return continueProgram;
}

bool CustomerController::handleMenu(Customer& customer) {
    int choice;
    bool continueProgram = true;

    while (continueProgram)
    {
        Display::printMessage(Messages::MSG_CUSTOMER_OPERATIONS_MENU);
        Display::printMessage(Messages::MSG_INPUT_CHOICE);

        InputHandler::inputValue(choice);
        continueProgram = handleChoice(choice, customer);
    }

    return continueProgram;
}
