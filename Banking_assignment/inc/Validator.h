#ifndef VALIDATOR_H
#define VALIDATOR_H

/**
 * @file Validator.h
 * @brief Declaration of ValidationResult and the Validator utility class.
 */

#include "Constants.h"
#include <string>

/**
 * @brief Represents the outcome of a validation check.
 *
 * Provides a clear, type-safe alternative to returning a bare @c bool from
 * validation functions.  On failure, the embedded @c errorMessage carries
 * a human-readable description of the violation ready to be displayed to
 * the user.
 *
 * ### Usage
 * @code
 * auto result = Validator::isValidInput(input, Constants::InputType::EMAIL);
 * if (!result) {
 *     Display::printMessage(result.errorMessage);
 * }
 * @endcode
 */
struct ValidationResult {
    bool valid;              ///< @c true when the input passed all checks.
    std::string errorMessage; ///< Human-readable error description; empty when valid.

    /**
     * @brief Implicit boolean conversion — @c true means valid.
     *
     * Allows ValidationResult to be used directly in conditionals:
     * @code if (auto r = validate(x); !r) { ... } @endcode
     */
    explicit operator bool() const { return valid; }

    /** @brief Factory: creates a passing result with an empty message. */
    static ValidationResult ok()                   { return {true,  {}}; }

    /**
     * @brief Factory: creates a failing result with an error message.
     * @param msg Human-readable description of the validation failure.
     */
    static ValidationResult fail(std::string msg)  { return {false, std::move(msg)}; }
};

/**
 * @brief Stateless collection of input validation rules.
 *
 * All methods are static — the class is a utility namespace rather than
 * an instantiable object.  Validation rules are purely data-driven; no I/O
 * is performed here (error messages are returned, not printed).
 */
class Validator {
    /** @brief Verifies digit-only content and exact length. */
    static ValidationResult isValidDigitsOnly(const std::string& input, size_t expectedLength);

    /** @brief Verifies minimum length and alpha+space character set. */
    static ValidationResult isValidName(const std::string& input);

    /**
     * @brief Applies basic structural email validation rules.
     *
     * Checks performed (in order):
     *  -# Presence of exactly one '@' character.
     *  -# At least one '.' after the '@' that is not the final character.
     *  -# No two consecutive '.' characters after the '@'.
     *
     * @note This is a structural sanity check, not full RFC 5321 compliance.
     */
    static ValidationResult isValidEmail(const std::string& email);

public:
    /**
     * @brief Checks whether the current @c std::cin state is valid and the
     *        next character is a newline (i.e., no unexpected trailing input).
     *
     * Clears any failbit, skips leading spaces/tabs, and consumes the rest
     * of the line.
     *
     * @return @c true if the stream was in a good state and the user pressed
     *         Enter without extra non-whitespace characters.
     */
    static bool isInputStreamValid();

    /**
     * @brief Validates @p input according to the rules for @p type.
     *
     * Dispatches to the appropriate private validation method based on
     * @p type.  The returned ValidationResult carries a display-ready
     * error message on failure so that the caller (InputHandler) can
     * relay it to the UI without knowing the specific rule that was violated.
     *
     * @param input The string to validate (must not be empty; InputHandler
     *              enforces this precondition before calling this method).
     * @param type  The expected input type that determines which rules apply.
     * @return A ValidationResult; evaluates to @c true when valid.
     */
    static ValidationResult isValidInput(const std::string& input, Constants::InputType type);
};

#endif
