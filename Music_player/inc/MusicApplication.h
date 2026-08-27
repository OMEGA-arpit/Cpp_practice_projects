#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <memory>
#include "IPlayerService.h"
#include "IPlaylistController.h"
#include "ILogger.h"
#include "IInputHandler.h"

class MusicApplication {
    // Declared in lifetime order: logger and inputHandler outlive service and controller
    std::unique_ptr<ILogger> logger;
    std::unique_ptr<IInputHandler> inputHandler;
    std::unique_ptr<IPlayerService> playerService;
    std::unique_ptr<IPlaylistController> playlistController;

    void handlePlayPrompt(const Song& song);
    void handleViewLibrary();
    void handleSearch();
    void handlePlayPause();
    bool handleChoice(int choice);

public:
    MusicApplication(std::unique_ptr<IPlayerService> service,
                     std::unique_ptr<IPlaylistController> controller,
                     std::unique_ptr<ILogger> logger,
                     std::unique_ptr<IInputHandler> inputHandler);

    void handleMainMenu();
};

#endif
