#ifndef CUSTOMER_H
#define CUSTOMER_H

/**
 * @file Customer.h
 * @brief Declaration of the Customer class, representing a registered bank customer.
 */

#include "User.h"
#include "Account.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Represents a registered bank customer.
 *
 * A Customer owns exactly one Account and holds their personal contact details.
 * Authentication is performed by matching the account number and PIN stored
 * within the embedded Account.
 */
class Customer : public User {
    std::string phone; ///< 10-digit phone number string.
    std::string email; ///< Email address string.
    Account account;   ///< The customer's sole bank account.

public:
    /**
     * @brief Constructs a Customer with personal details.
     *
     * The Role is set to CUSTOMER automatically.  Account number and PIN
     * must be assigned separately via the embedded Account object.
     *
     * @param name  Display name (must satisfy Validator::isValidName constraints).
     * @param email Email address.
     * @param phone 10-digit phone number.
     */
    Customer(const std::string& name, const std::string& email, const std::string& phone)
        : email{email}, phone{phone} {
        this->name = name;
        this->role = Constants::UserRole::CUSTOMER;
    }

    /**
     * @brief Returns a mutable reference to the customer's account.
     *
     * Used by controllers and services to perform deposits, withdrawals, etc.
     */
    Account& getAccount() { return account; }

    /**
     * @brief Returns a read-only reference to the customer's account.
     */
    const Account& getAccount() const { return account; }

    /** @brief Returns the customer's phone number. */
    std::string getPhone() const { return phone; }

    /** @brief Returns the customer's email address. */
    std::string getEmail() const { return email; }

    /**
     * @brief Updates the customer's email address.
     * @param email The new email address.
     */
    void setEmail(const std::string& email) { this->email = email; }

    /**
     * @brief Updates the customer's phone number.
     * @param phone The new 10-digit phone number.
     */
    void setPhone(const std::string& phone) { this->phone = phone; }

    /**
     * @brief Verifies the account number and PIN combination.
     *
     * Delegates to the embedded Account for PIN verification.
     *
     * @param accountNumber Account number to check.
     * @param accountPin    PIN to check.
     * @return @c true if both match the values stored in the Account.
     */
    [[nodiscard]] bool authenticate(const std::string& accountNumber, const std::string& accountPin) const override {
        return (this->account.getAccountNumber() == accountNumber)
         && this->account.verifyPin(accountPin);
    }

    /** @brief Prints name, email, phone and account number to stdout. */
    void displayInformation() const override;

    /** @brief Prints account number and current balance to stdout. */
    void displayAccountDetails() const;
};

#endif
