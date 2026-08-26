#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

/**
 * @file AdminController.h
 * @brief Declaration of AdminController, which orchestrates all admin use-cases.
 */

#include "CustomerService.h"
#include "CustomerController.h"

/**
 * @brief Handles all administrator operations accessible from the admin menu.
 *
 * AdminController mediates between the UI (Display / InputHandler) and the
 * domain layer (CustomerService, CustomerController).  It owns no data;
 * all persistent state lives in CustomerService.
 */
class AdminController {
    CustomerService* customerService;     ///< Non-owning pointer to the shared customer store.
    CustomerController* customerController; ///< Non-owning pointer used for account operations.

    bool handleMenuChoice(int choice);
    bool handleEditMenuChoice(int choice, Customer* customer);

    void registerCustomer();

    void updateCustomerName(Customer* customer);
    void updateCustomerEmail(Customer* customer);
    void updateCustomerPhone(Customer* customer);
    void updateCustomerPin(Customer* customer);
    void editCustomerDetails();
    void handleCustomerDeletion();

    void displayCustomersInformation();
    void displayAccountsInformation();

    void displayCustomerByAccountNumber();
    void displayAccountByNumber();

    void manageCustomerAccount();
    void performAccountOperation(Customer* customer);

public:
    /**
     * @brief Constructs an AdminController backed by the given service and controller.
     * @param service    Pointer to the shared CustomerService. Must outlive this object.
     * @param controller Pointer to the CustomerController used for account transactions.
     */
    AdminController(CustomerService* service, CustomerController* controller) :
    customerService{service}, customerController{controller} {}

    /**
     * @brief Displays the admin menu in a loop until the admin logs out.
     * @return @c true if the session ended normally (logout); reserved for future use.
     */
    bool handleMenu();
};

#endif
