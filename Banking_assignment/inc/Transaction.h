#ifndef TRANSACTION_H
#define TRANSACTION_H

/**
 * @file Transaction.h
 * @brief Declaration of the Transaction class, representing a single debit or credit event.
 */

#include "Constants.h"

class Bank;

/**
 * @brief An immutable record of a single financial transaction.
 *
 * Each Transaction is assigned a system-wide unique, monotonically
 * increasing ID at construction time.  The post-transaction balance is
 * stored for statement rendering so the Account need not be queried
 * retrospectively.
 */
class Transaction {
    long id;
    Constants::TransactionType type;
    double postTransactionBalance;
    double amount;

    static long transactionIdCounter; ///< Shared counter; starts at INITIAL_TRANSACTION_ID.

public:
    /**
     * @brief Constructs a Transaction and assigns the next sequential ID.
     * @param transactionType Whether this is a DEPOSIT or WITHDRAWAL.
     * @param amount          The monetary amount of the transaction.
     * @param postBalance     The account balance immediately after this transaction.
     */
    Transaction(Constants::TransactionType transactionType,
        double amount, double postBalance);

    /** @brief Returns the unique transaction ID. */
    long getId() const { return id; }

    /** @brief Returns the transaction type (DEPOSIT or WITHDRAWAL). */
    Constants::TransactionType getType() const { return type; }

    /** @brief Returns the account balance recorded after this transaction. */
    double getPostBalance() const { return postTransactionBalance; }

    /** @brief Returns the monetary amount of this transaction. */
    double getAmount() const { return amount; }

    /**
     * @brief Overwrites the stored post-transaction balance.
     * @param balance The corrected post-balance value.
     * @note Intended for administrative correction only; normal use should not call this.
     */
    void setPostBalance(double balance) { postTransactionBalance = balance; }

};

#endif
