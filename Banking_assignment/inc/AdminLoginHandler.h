#ifndef ADMIN_LOGIN_HANDLER_H
#define ADMIN_LOGIN_HANDLER_H

/**
 * @file AdminLoginHandler.h
 * @brief Declaration of AdminLoginHandler.
 */

#include "ILoginHandler.h"
#include "Admin.h"
#include "CustomerService.h"
#include "AdminController.h"

/**
 * @brief Handles the admin authentication flow.
 *
 * Collects a username and password from stdin, verifies them against the
 * Admin object, and — on success — delegates control to AdminController
 * for the duration of the admin session.
 */
class AdminLoginHandler : public ILoginHandler {
    Admin& admin;                  ///< Reference to the singleton Admin entity.
    AdminController* adminController; ///< Non-owning pointer to the admin menu controller.

    /** @brief Reads credentials from stdin and returns whether they are correct. */
    bool getAndVerifyCredentials();

public:
    /**
     * @brief Constructs the handler with the required collaborators.
     * @param admin      Reference to the Admin entity used for credential verification.
     * @param controller Non-owning pointer to the AdminController; must outlive this object.
     */
    AdminLoginHandler(Admin& admin, AdminController* controller)
        : admin{admin}, adminController{controller} {}

    /**
     * @brief Attempts admin authentication and, on success, opens the admin menu.
     * @return LoginResult::SUCCESS when authenticated; LoginResult::FAILED otherwise.
     */
    Constants::LoginResult login() override;

    /** @brief Clears the screen and prints a logout confirmation message. */
    void logout() override;
};

#endif
