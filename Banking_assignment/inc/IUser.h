#ifndef IUSER_H
#define IUSER_H

/**
 * @file IUser.h
 * @brief Abstract interface representing any authenticated user in the system.
 */

#include <string>
#include "Constants.h"

/**
 * @brief Abstract base for all user types (Admin, Customer).
 *
 * Defines the contract that every user entity must fulfil:
 * credential verification and self-display.
 */
class IUser {
public:
    /**
     * @brief Verifies the supplied credentials against the stored ones.
     * @param credential1 Primary credential (username or account number).
     * @param credential2 Secondary credential (password or PIN).
     * @return @c true if both credentials are correct.
     */
    virtual bool authenticate(const std::string& credential1,
                            const std::string& credential2) const = 0;

    /**
     * @brief Prints the user's identifying information to stdout.
     */
    virtual void displayInformation() const = 0;

    virtual ~IUser() = default;
};

#endif
