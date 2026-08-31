#ifndef BANK_H
#define BANK_H

/**
 * @file Bank.h
 * @brief Declaration of the Bank class — the central application object.
 */

#include "Customer.h"
#include "Admin.h"
#include "AdminController.h"
#include "CustomerController.h"
#include "AdminLoginHandler.h"
#include "CustomerLoginHandler.h"
#include "IBank.h"
#include "ILoginHandler.h"
#include "Constants.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @brief Central application object that owns all subsystems and drives the
 *        main menu loop.
 *
 * Bank wires together the CustomerService, Admin entity, two controllers,
 * and two login handlers.  Ownership of controllers and handlers is expressed
 * through smart pointers:
 *  - Controllers are @c unique_ptr (exclusively owned by Bank).
 *  - Handlers are @c shared_ptr, which allows the test constructor to inject
 *    externally-owned mock objects via a no-op custom deleter.
 *
 * ### Normal construction
 * @code
 * Bank bank; // creates all subsystems internally
 * BankingSystem system(&bank);
 * system.execute();
 * @endcode
 *
 * ### Test construction (dependency injection)
 * @code
 * MockLoginHandler mockAdmin, mockCustomer;
 * Bank bank(&mockAdmin, &mockCustomer);
 * @endcode
 */
class Bank : public IBank {
    CustomerService customerService;
    Admin admin;
    std::unique_ptr<CustomerController> customerController;
    std::unique_ptr<AdminController> adminController;
    std::shared_ptr<ILoginHandler> adminLoginHandler;
    std::shared_ptr<ILoginHandler> customerLoginHandler;

public:
    /**
     * @brief Default constructor — creates and owns all internal subsystems.
     *
     * Instantiation order matters: CustomerController must exist before
     * AdminController (which takes a raw pointer to it), and both controllers
     * must exist before the login handlers.
     */
    Bank();

    /**
     * @brief Injection constructor for testing.
     *
     * Wraps the supplied raw pointers in @c shared_ptr with a no-op deleter so
     * that Bank does not destroy externally-owned mock objects on destruction.
     * The adminController and customerController are left null (nullptr) because
     * test scenarios only exercise Bank::login() / handleChoice(), not the menus.
     *
     * @param adminHandler    Non-owning pointer to an ILoginHandler for admin login.
     * @param customerHandler Non-owning pointer to an ILoginHandler for customer login.
     */
    Bank(ILoginHandler* adminHandler, ILoginHandler* customerHandler);

    /**
     * @brief Processes a single menu choice from the top-level menu.
     *
     * Choice 1 → admin login, 2 → customer login, 3 → exit.
     *
     * @param choice The integer entered by the user.
     * @return @c true to continue the program loop; @c false to exit.
     */
    [[nodiscard]] bool handleChoice(int choice);

    /**
     * @brief Runs the top-level menu loop until the user exits.
     *
     * Prints the welcome menu, reads a choice, and dispatches to handleChoice()
     * in a loop.  Returns when choice 3 is selected or login repeatedly fails.
     */
    void handleMenu() override;

    /**
     * @brief Attempts to authenticate a user of @p role.
     *
     * Retries up to MAX_LOGIN_ATTEMPTS times on FAILED results.  An
     * ACCOUNT_NOT_FOUND result is treated as a non-error (the user entered a
     * non-existent account and is simply returned to the main menu).
     *
     * @param role The role to authenticate (ADMIN or CUSTOMER).
     * @return @c true if login succeeded or the account was not found; @c false
     *         if the maximum number of failed attempts was exhausted.
     */
    [[nodiscard]] bool login(Constants::UserRole role) override;
};

#endif
