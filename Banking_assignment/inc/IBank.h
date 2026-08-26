#ifndef IBANK_H
#define IBANK_H

/**
 * @file IBank.h
 * @brief Abstract interface for the top-level bank object.
 */

#include "Constants.h"
#include <string>
#include <vector>

class Customer;

/**
 * @brief Abstract interface exposing the two responsibilities of a Bank:
 *        displaying the main menu and authenticating a user by role.
 *
 * Separating these into an interface enables the class to be mocked in
 * tests without depending on real I/O or data.
 */
class IBank {
public:
    virtual ~IBank() = default;

    /**
     * @brief Runs the main application loop, displaying the top-level menu
     *        and dispatching role-based logins until the user exits.
     */
    virtual void handleMenu() = 0;

    /**
     * @brief Attempts to authenticate a user of the given role.
     *
     * Delegates to the appropriate login handler and retries up to
     * @c MAX_LOGIN_ATTEMPTS times on failure.
     *
     * @param role The role to authenticate as (ADMIN or CUSTOMER).
     * @return @c true if authentication succeeded or the account was not found
     *         (non-blocking exit); @c false if the maximum attempts were exhausted.
     */
    [[nodiscard]] virtual bool login(Constants::UserRole role) = 0;
};

#endif
