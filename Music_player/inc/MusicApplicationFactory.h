#ifndef MUSIC_APPLICATION_FACTORY_H
#define MUSIC_APPLICATION_FACTORY_H

#include <memory>
#include "MusicApplication.h"

/**
 * @brief Constructs and wires the complete MusicApplication object graph.
 *
 * This is the single composition root for the application. It creates every
 * concrete object in the correct order, establishes ownership via unique_ptr,
 * and injects dependencies through constructor parameters.
 *
 * Typical usage:
 * @code
 *   MusicApplicationFactory factory;
 *   auto app = factory.create();
 *   app->handleMainMenu();
 * @endcode
 */
class MusicApplicationFactory {
public:
    /**
     * @brief Builds the fully wired application instance.
     * @return Owning pointer to a ready-to-use MusicApplication.
     */
    std::unique_ptr<MusicApplication> create();
};

#endif
