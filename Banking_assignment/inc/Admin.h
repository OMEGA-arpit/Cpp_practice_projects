#ifndef ADMIN_H
#define ADMIN_H

/**
 * @file Admin.h
 * @brief Declaration of the Admin class, representing the single system administrator.
 */

#include "Constants.h"
#include "User.h"
#include <string>

/**
 * @brief Represents the single, statically-configured system administrator.
 *
 * The administrator's credentials are initialised from the constants defined
 * in Constants.h.  There is exactly one admin in the system; no runtime
 * registration is supported.
 *
 * @note In a production system, credentials should be stored as a salted hash,
 *       not as plaintext constants.
 */
class Admin : public User {
    std::string userName; ///< Login username.
    std::string password; ///< Plaintext password (see note above).

public:
    /**
     * @brief Constructs the Admin with hardcoded system credentials.
     *
     * Name, username and password are read from Constants::ADMIN_NAME,
     * Constants::ADMIN_USERNAME and Constants::ADMIN_PASSWORD respectively.
     */
    Admin() : userName{Constants::ADMIN_USERNAME}, password{Constants::ADMIN_PASSWORD} {
        this->name = Constants::ADMIN_NAME;
        this->role = Constants::UserRole::ADMIN;
    }

    /**
     * @brief Verifies the supplied admin credentials.
     * @param userName The username to check.
     * @param password The password to check.
     * @return @c true if both match the stored values exactly.
     */
    [[nodiscard]] bool authenticate(const std::string& userName, const std::string& password) const override {
        return (this->userName == userName) && (this->password == password);
    }

    /** @brief Prints the admin's name and username to stdout. */
    void displayInformation() const override;
};

#endif
