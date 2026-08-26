#ifndef CUSTOMER_LOGIN_HANDLER_H
#define CUSTOMER_LOGIN_HANDLER_H

/**
 * @file CustomerLoginHandler.h
 * @brief Declaration of CustomerLoginHandler.
 */

#include "ILoginHandler.h"
#include "CustomerService.h"
#include "CustomerController.h"

/**
 * @brief Handles the customer authentication flow.
 *
 * Prompts for an account number, looks it up in CustomerService, then
 * prompts for a PIN.  On success, delegates control to CustomerController
 * for the duration of the customer session.
 */
class CustomerLoginHandler : public ILoginHandler {
    CustomerService& customerService;     ///< Reference to the customer data store.
    CustomerController* customerController; ///< Non-owning pointer to the customer menu controller.

    /**
     * @brief Reads an account number from stdin and looks up the corresponding Customer.
     * @return Pointer to the Customer if found; @c nullptr if the account does not exist.
     */
    Customer* getCustomer();

    /**
     * @brief Reads a PIN from stdin and verifies it against @p customer's account.
     * @param customer The customer whose PIN to verify.
     * @return @c true if the entered PIN is correct.
     */
    bool verifyPin(Customer* customer);

public:
    /**
     * @brief Constructs the handler with the required collaborators.
     * @param service    Reference to the CustomerService for account lookup.
     * @param controller Non-owning pointer to CustomerController; must outlive this object.
     */
    CustomerLoginHandler(CustomerService& service, CustomerController* controller)
        : customerService{service}, customerController{controller} {}

    /**
     * @brief Attempts customer authentication and, on success, opens the customer menu.
     * @return LoginResult::SUCCESS on correct credentials;
     *         LoginResult::ACCOUNT_NOT_FOUND if the account number does not exist;
     *         LoginResult::FAILED if the PIN is wrong.
     */
    Constants::LoginResult login() override;

    /** @brief Clears the screen and prints a logout confirmation message. */
    void logout() override;
};

#endif
