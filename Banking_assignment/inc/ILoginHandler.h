#ifndef ILOGIN_HANDLER_H
#define ILOGIN_HANDLER_H

/**
 * @file ILoginHandler.h
 * @brief Abstract interface for role-specific login handlers.
 */

#include "Constants.h"

/**
 * @brief Abstract interface for objects that manage a single login session.
 *
 * Concrete implementations (AdminLoginHandler, CustomerLoginHandler)
 * collect credentials, verify them, launch the post-login menu, and
 * handle logout. Abstracting this behind an interface allows Bank to
 * remain decoupled from any particular authentication strategy and
 * enables straightforward mock injection in tests.
 */
class ILoginHandler {
public:
    /**
     * @brief Attempts to authenticate the user and — on success — launches
     *        the corresponding menu until logout.
     * @return The outcome of the login attempt.
     */
    virtual Constants::LoginResult login() = 0;

    /**
     * @brief Logs the current user out and clears the screen.
     */
    virtual void logout() = 0;

    virtual ~ILoginHandler() = default;
};

#endif
