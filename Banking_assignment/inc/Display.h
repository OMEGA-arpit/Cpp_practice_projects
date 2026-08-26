#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @file Display.h
 * @brief Stateless console output utilities.
 */

#include <string>
#include <iostream>

/**
 * @brief Provides static helper methods for all console output.
 *
 * Centralises formatting logic so that controllers and entities never
 * write to @c std::cout directly.  All methods are static — the class
 * is a utility namespace rather than an instantiable object.
 */
class Display {
public:
    /** @brief Writes @p message to stdout without a trailing newline. */
    static void printMessage(const std::string& message);

    /**
     * @brief Writes @p prefix, then @p value, then @p suffix to stdout.
     * @param prefix  Text before the numeric value.
     * @param value   The numeric value to display.
     * @param suffix  Text after the numeric value.
     */
    static void printWithSuffix(const std::string& prefix, size_t value, const std::string& suffix);

    /**
     * @brief Writes @p message followed by @p number and a newline.
     * @param message Label text.
     * @param number  The numeric value to append.
     */
    static void printWithNumber(const std::string& message, size_t number);

    /**
     * @brief Writes @p message followed by @p value and a newline.
     * @param message Label text.
     * @param value   The string value to append.
     */
    static void printWithValue(const std::string& message, const std::string& value);

    /**
     * @brief Writes @p message followed by @p amount formatted to 2 decimal places.
     * @param message Label text.
     * @param amount  Monetary amount to display.
     */
    static void printWithAmount(const std::string& message, double amount);

    /** @brief Prints the column headers for a transaction table. */
    static void printTransactionHeader();

    /**
     * @brief Prints a single formatted transaction row.
     * @param id          Transaction ID.
     * @param type        Human-readable type string ("Deposit" / "Withdrawal").
     * @param amount      Transaction amount.
     * @param postBalance Account balance after the transaction.
     */
    static void printTransactionRow(long id, const std::string& type, double amount, double postBalance);

    /** @brief Prints the allowed transaction amount range as a single line. */
    static void printTransactionRange();

    /**
     * @brief Clears the terminal screen using an ANSI escape sequence.
     *
     * Works on any ANSI-compatible terminal (Linux, macOS, Windows Terminal).
     */
    static void clearScreen();
};

#endif
