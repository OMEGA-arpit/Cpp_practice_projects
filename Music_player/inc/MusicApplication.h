#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "IPlayerService.h"
#include "IPlaylistController.h"
#include "ILogger.h"
#include "IInputHandler.h"

class MusicApplication {
    IPlayerService* playerService;
    IPlaylistController* playlistController;
    ILogger* logger;
    IInputHandler* inputHandler;  

    void handlePlayPrompt(const Song& song);
    void handleViewLibrary();
    void handleSearch();
    void handlePlayPause();
    bool handleChoice(int choice);

public:
    MusicApplication(IPlayerService* service, 
        IPlaylistController* controller, ILogger* logger, IInputHandler* inputHandler) 
    : playerService(service), playlistController(controller),
    logger(logger), inputHandler(inputHandler) {}

    void handleMainMenu();

    ~MusicApplication();
};

#endif
