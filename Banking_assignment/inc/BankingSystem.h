#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

/**
 * @file BankingSystem.h
 * @brief Declaration of BankingSystem, the application entry-point facade.
 */

#include "IBank.h"
#include "Bank.h"

/**
 * @brief Thin facade that launches a Bank through the IBank interface.
 *
 * Decouples @c main() from the concrete Bank type, making it trivial to
 * inject a MockBank in integration tests without changing the call site.
 */
class BankingSystem {
    IBank* bank; ///< Non-owning pointer to the active bank implementation.

public:
    /**
     * @brief Constructs a BankingSystem backed by @p currentBank.
     * @param currentBank Pointer to an IBank implementation.  Must outlive this object.
     */
    BankingSystem(IBank* currentBank) : bank(currentBank) {}

    /**
     * @brief Starts the application by invoking the bank's main menu loop.
     *
     * Returns when the user exits from the top-level menu.
     */
    void execute() { bank->handleMenu(); }
};

#endif
