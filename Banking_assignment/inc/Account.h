#ifndef ACCOUNT_H
#define ACCOUNT_H

/**
 * @file Account.h
 * @brief Declaration of the Account class, representing a customer's bank account.
 */

#include "Transaction.h"
#include "Constants.h"
#include <string>
#include <vector>

/**
 * @brief Represents a single bank account with a balance and transaction history.
 *
 * An Account owns its PIN, account number, current balance, and the ordered
 * list of all transactions that have been applied to it.  All monetary
 * operations enforce the configured per-transaction limits defined in
 * Constants (MIN_TRANSACTION_AMOUNT / MAX_TRANSACTION_AMOUNT).
 */
class Account {
    std::string accountNumber;
    std::string pin;
    double balance;
    std::vector<Transaction> transactions;

    /**
     * @brief Returns @c true when @p amount is within the allowed range.
     *
     * Valid range: [MIN_TRANSACTION_AMOUNT, MAX_TRANSACTION_AMOUNT] (inclusive).
     */
    bool isValidAmount(double amount) const {
        return amount >= Constants::MIN_TRANSACTION_AMOUNT
            && amount <= Constants::MAX_TRANSACTION_AMOUNT;
    }

public:
    /** @brief Constructs an Account with a zero starting balance. */
    Account() : balance{0.0} {}

    /** @brief Returns the account number string. */
    const std::string& getAccountNumber() const { return accountNumber; }

    /** @brief Returns the current balance. */
    double getBalance() const { return balance; }

    /**
     * @brief Returns a read-only reference to the full transaction history.
     *
     * The vector is ordered chronologically; index 0 is the oldest transaction.
     */
    const std::vector<Transaction>& getTransactions() const { return transactions; }

    /**
     * @brief Replaces the stored PIN.
     * @param pin The new PIN string.  No validation is performed here;
     *            callers are responsible for ensuring the value is a valid 4-digit string.
     */
    void setPin(const std::string& pin) { this->pin = pin; }

    /** @brief Replaces the account number. @param accountNumber The new account number string. */
    void setAccountNumber(const std::string& accountNumber) { this->accountNumber = accountNumber; }

    /**
     * @brief Sets the balance to @p balance directly.
     *
     * Negative values are silently rejected.
     *
     * @param balance New balance value (must be ≥ 0).
     * @note Intended for administrative seeding; prefer deposit() / withdrawal() for normal use.
     */
    void setBalance(double balance) {
        if (balance >= 0.0)
        {
            this->balance = balance;
        }
    }

    /** @brief Appends @p transaction to the internal history. */
    void addTransaction(const Transaction& transaction) { transactions.push_back(transaction); }

    /**
     * @brief Checks whether @p inputPin matches the stored PIN.
     * @param inputPin The PIN to verify.
     * @return @c true if the PINs match exactly.
     */
    bool verifyPin(const std::string& inputPin) const { return (pin == inputPin); }

    /**
     * @brief Credits the account by @p amount.
     *
     * Validates the amount is within [MIN_TRANSACTION_AMOUNT, MAX_TRANSACTION_AMOUNT],
     * adds the amount to the balance, and records a DEPOSIT transaction.
     *
     * @param amount Positive amount to deposit.
     * @return @c true on success; @c false if @p amount is out of the allowed range.
     */
    [[nodiscard]] bool deposit(double amount);

    /**
     * @brief Debits the account by @p amount.
     *
     * Validates the amount is within range and that the balance covers it,
     * subtracts the amount from the balance, and records a WITHDRAWAL transaction.
     *
     * @param amount Positive amount to withdraw.
     * @return @c true on success; @c false if @p amount is out of range or
     *         the current balance is insufficient.
     */
    [[nodiscard]] bool withdrawal(double amount);

    /**
     * @brief Returns the @p count most recent transactions.
     *
     * If fewer than @p count transactions exist, all are returned.
     * If @p count is 0 or the history is empty, an empty vector is returned.
     *
     * @param count Maximum number of transactions to retrieve.
     * @return A new vector containing up to @p count transactions, in chronological order.
     */
    std::vector<Transaction> getLastTransactions(int count);
};

#endif
