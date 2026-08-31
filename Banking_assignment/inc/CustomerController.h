#ifndef Customer_CONTROLLER_H
#define Customer_CONTROLLER_H

/**
 * @file CustomerController.h
 * @brief Declaration of CustomerController, which orchestrates customer self-service operations.
 */

#include "Customer.h"

/**
 * @brief Handles all customer-facing operations accessible from the customer menu.
 *
 * CustomerController mediates between the UI (Display / InputHandler) and
 * the Customer/Account domain objects.  It holds no state; the Customer
 * reference passed to each method is the single source of truth.
 */
class CustomerController {
    bool changePin(Customer& customer);
    bool isOldPinCorrect(Account& account);

    void displayMiniStatement(Customer& customer);
    void displayBankStatement(Customer& customer);

    bool handleChoice(int choice, Customer& customer);

public:
    /**
     * @brief Prompts the user for a deposit amount and credits the account.
     * @param customer The customer whose account to credit.
     */
    void performDeposit(Customer& customer);

    /**
     * @brief Prompts the user for a withdrawal amount and debits the account.
     * @param customer The customer whose account to debit.
     */
    void performWithdrawal(Customer& customer);

    /**
     * @brief Displays the customer menu in a loop until the customer logs out.
     * @param customer The authenticated customer for this session.
     * @return @c false when the session should end (logout or PIN change).
     */
    bool handleMenu(Customer& customer);
};

#endif
