#ifndef I_USER_CONTROLLER_H
#define I_USER_CONTROLLER_H

/**
 * @brief Manages the interactive driver-query loop on the input thread.
 *
 * Prompts the user for their lane and destination, computes the move type
 * and wait time, and displays a result. Loops until the user exits.
 */
class IUserController {
public:
    /**
     * @brief Enters the query loop. Blocks until the user chooses to stop.
     */
    virtual void handleUserQueries() = 0;

    virtual ~IUserController() = default;
};

#endif
