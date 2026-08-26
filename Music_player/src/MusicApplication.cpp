#include "MusicApplication.h"
#include <string>

void MusicApplication::handleViewLibrary() {
    const std::set<Song>& songs = playerService->getAllSongs();

    logger->printMessage(Constants::MSG_LIBRARY_HEADER);

    if (songs.empty()) 
    {
        logger->printMessage(Constants::MSG_LIBRARY_EMPTY);
    }
    else
    {
        int index = 1;
        for (const Song& song : songs) 
        {
            logger->printMessage(std::to_string(index++) + Constants::FULL_STOP
            + Constants::WHITESPACE + song.name);
            logger->printNewLine();
        }
    }
}

void MusicApplication::handlePlayPrompt(const Song& song) {
    logger->printMessage(Constants::MSG_PLAY_PROMPT);

    char userChoice = inputHandler->inputCharacter();

    if (userChoice == Constants::CHARACTER_P) 
    {
        if (playerService->playSong(song)) 
        {
            logger->printMessage(Constants::MSG_NOW_PLAYING + song.name);
            logger->printNewLine();
        }
    }
    else if (userChoice != Constants::CHARACTER_B)
    {
        logger->printMessage(Constants::MSG_INVALID_CHOICE);
    }
}

void MusicApplication::handleSearch() {
    logger->printMessage(Constants::MSG_SEARCH_PROMPT);
    std::string title;
    inputHandler->inputString(title);

    const Song* result = playerService->searchSong(title);

    if (!result) 
    {
        logger->printMessage(Constants::MSG_SEARCH_EMPTY);  
    }
    else
    {
        logger->printMessage(Constants::MSG_FOUND + result->name);
        handlePlayPrompt(*result);
    }
}

void MusicApplication::handlePlayPause() {
    if (playerService->isPlaying()) 
    {
        playerService->pause();
        logger->printMessage(Constants::MSG_PAUSED_SONG);
    }
    else 
    {
        playerService->resume();
        logger->printMessage(Constants::MSG_PLAYING_SONG);
    }
}

bool MusicApplication::handleChoice(int choice) {
    bool continueProgram = true;

    switch (choice)
    {
        case 1:
            playlistController->handlePlaylistMenu();
            break;

        case 2:
            handleViewLibrary();
            break;

        case 3:
            handleSearch();
            break;
            
        case 4:
            handlePlayPause();
            break;

        case 5:
            playerService->savePlaylists();
            continueProgram = false;
            break;

        default:
            logger->printMessage(Constants::MSG_INVALID_CHOICE);
    }
    
    return continueProgram;
}

void MusicApplication::handleMainMenu() {
    logger->printMessage(Constants::MSG_WELCOME);
    playerService->loadPlaylists();

    while (true) 
    {
        playerService->checkAndAdvance();
        logger->printMessage(Constants::MSG_MAIN_MENU);
        logger->printMessage(Constants::MSG_INPUT_CHOICE);

        int choice = inputHandler->inputValue();
        if (!handleChoice(choice))
        {
            logger->printMessage(Constants::MSG_PROGRAM_EXIT);
            return;
        }
    }
}

MusicApplication::~MusicApplication() {
    delete playlistController;
    delete playerService;    
    delete logger;
    delete inputHandler;
}
