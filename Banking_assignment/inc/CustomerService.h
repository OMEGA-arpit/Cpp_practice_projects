#ifndef CUSTOMER_SERVICE_H
#define CUSTOMER_SERVICE_H

/**
 * @file CustomerService.h
 * @brief Declaration of CustomerService and the RegistrationResult value object.
 */

#include "Customer.h"
#include <list>

/**
 * @brief Carries the data produced by a successful customer registration.
 *
 * Returned by CustomerService::createCustomer() so that the caller (typically
 * AdminController) can display the auto-generated credentials to the admin
 * without CustomerService needing to know anything about the UI layer.
 */
struct RegistrationResult {
    Customer* customer;        ///< Pointer to the newly created Customer (owned by CustomerService).
    std::string accountNumber; ///< Auto-generated 8-digit account number.
    std::string pin;           ///< Randomly generated 4-digit PIN.
};

/**
 * @brief Manages the lifecycle of all Customer objects in the system.
 *
 * Provides CRUD operations for customers, account number sequencing,
 * and random PIN generation.  Customers are stored in a @c std::list to
 * ensure that pointers returned by findCustomerByAccountNumber() remain
 * stable across subsequent createCustomer() calls — unlike @c std::vector,
 * @c std::list does not relocate elements on insertion.
 */
class CustomerService {
    std::list<Customer> customers; ///< Stable-pointer storage for all customers.
    static long accountNumberCounter; ///< Monotonically increasing account number seed.

    /**
     * @brief Generates a random 4-digit PIN in [MIN_PIN_VALUE, MAX_PIN_VALUE].
     *
     * Uses a static Mersenne-Twister seeded from a hardware entropy source on
     * the first call; subsequent calls reuse the same generator instance to
     * avoid re-seeding overhead.
     *
     * @return A 4-character numeric string representing the PIN.
     */
    static std::string generateRandomPin();

public:
    /**
     * @brief Creates a new Customer, assigns a unique account number and random PIN,
     *        and stores it in the internal list.
     *
     * @param name  Customer's full name.
     * @param email Customer's email address.
     * @param phone Customer's 10-digit phone number.
     * @return A RegistrationResult containing a pointer to the new Customer and its credentials.
     * @note The returned pointer is stable for the lifetime of this CustomerService instance.
     */
    RegistrationResult createCustomer(const std::string& name,
                                      const std::string& email,
                                      const std::string& phone);

    /** @brief Returns a mutable reference to the internal customer list. */
    std::list<Customer>& getCustomers() { return customers; }

    /** @brief Returns a read-only reference to the internal customer list. */
    const std::list<Customer>& getCustomers() const { return customers; }

    /**
     * @brief Finds a Customer by account number.
     * @param accountNumber The 8-digit account number to search for.
     * @return A pointer to the matching Customer, or @c nullptr if not found.
     * @note The returned pointer remains valid as long as the customer has not been deleted.
     */
    Customer* findCustomerByAccountNumber(const std::string& accountNumber);

    /**
     * @brief Removes the Customer with the given account number from the system.
     *
     * Deletion is refused when the customer's account balance is non-zero.
     * The caller must arrange for all funds to be withdrawn first.
     *
     * @param accountNumber The account number of the customer to delete.
     * @return @c true if the customer was found and successfully removed; @c false otherwise.
     */
    bool deleteCustomerFromBank(const std::string& accountNumber);
};

#endif
