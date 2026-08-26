#ifndef USER_H
#define USER_H

/**
 * @file User.h
 * @brief Declaration of the User base class shared by Admin and Customer.
 */

#include "IUser.h"
#include "Constants.h"

/**
 * @brief Abstract base class that holds the properties common to all users.
 *
 * Provides storage and accessors for the name and role, delegating
 * the authentication and display contracts to concrete subclasses.
 */
class User : public IUser {
protected:
    std::string name; ///< Display name of the user.
    Constants::UserRole role; ///< Role assigned at construction.

public:
    /** @brief Returns the user's display name. */
    std::string getName() const { return name; }

    /** @brief Returns the user's role (ADMIN or CUSTOMER). */
    Constants::UserRole getRole() const { return role; }

    /**
     * @brief Updates the user's display name.
     * @param name The new name string.
     */
    void setName(const std::string& name) { this->name = name; }
};

#endif
