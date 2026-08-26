#include "PlaylistController.h"
#include "Constants.h"

PlaylistController::PlaylistController(IPlayerService* playerService,
                                       ILogger* logger,
                                       IInputHandler* inputHandler)
    : playerService(playerService)
    , logger(logger)
    , inputHandler(inputHandler) {}

void PlaylistController::handlePlay(IPlaylist* activePlaylist) {
    Song* currentSong = activePlaylist->getCurrentSong();

    if (currentSong != nullptr) 
    {
        if (playerService->playSong(*currentSong)) 
        {
            logger->printMessage(Constants::MSG_PLAYING_SONG);
            activePlaylist->setState(Constants::PlaybackState::PLAYING);
        } 
        else 
        {
            activePlaylist->setState(Constants::PlaybackState::STOPPED);
        }
    } 
    else 
    {
        logger->printMessage(Constants::MSG_PLAYLIST_EMPTY);
    }
}

void PlaylistController::handlePlayPause() {
    IPlaylist* activePlaylist = playerService->getActivePlaylist();

    if (activePlaylist->getState() == Constants::PlaybackState::PLAYING) 
    {
        playerService->pause();
        logger->printMessage(Constants::MSG_PAUSED_SONG);
        activePlaylist->setState(Constants::PlaybackState::PAUSED);
    } 
    else 
    {
        handlePlay(activePlaylist);
    }
}

void PlaylistController::displayLibrarySongs() {
    const std::set<Song>& songs = playerService->getAllSongs();
    IPlaylist* activePlaylist = playerService->getActivePlaylist();

    logger->printMessage(Constants::MSG_LIBRARY_HEADER);

    if (songs.empty()) {
        logger->printMessage(Constants::MSG_LIBRARY_EMPTY);
    } else {
        int index = 1;
        for (const Song& song : songs) 
        {
            bool alreadyAdded = (activePlaylist->searchSong(song.name) != nullptr);
            std::string marker = alreadyAdded ? Constants::MSG_ADDED : Constants::EMPTY_STRING;
            logger->printMessage(std::to_string(index) + Constants::FULL_STOP
            + Constants::WHITESPACE + song.name + marker);
            logger->printNewLine();
            index++;
        }
        logger->printNewLine();
    }
}

void PlaylistController::handleAddSong() {
    displayLibrarySongs();

    logger->printMessage(Constants::MSG_ENTER_SONG_NAME);

    std::string songName;
    inputHandler->inputString(songName);

    const Song* foundSong = playerService->searchSong(songName);

    if (foundSong == nullptr) 
    {
        logger->printMessage(Constants::MSG_SEARCH_EMPTY);
    } 
    else 
    {
        IPlaylist* activePlaylist = playerService->getActivePlaylist();

        if (activePlaylist->addSong(*foundSong)) 
        {
            logger->printMessage(Constants::MSG_SONG_ADDED);
        } 
        else 
        {
            logger->printMessage(Constants::MSG_SONG_ALREADY_EXISTS);
        }
    }
}

void PlaylistController::handleRemoveSong() {
    logger->printMessage(Constants::MSG_ENTER_SONG_NAME);

    std::string songName;
    inputHandler->inputString(songName);

    IPlaylist* activePlaylist = playerService->getActivePlaylist();

    if (activePlaylist->removeSong(songName)) 
    {
        logger->printMessage(Constants::MSG_SONG_REMOVED);
    } 
    else 
    {
        logger->printMessage(Constants::MSG_SONG_NOT_FOUND);
    }
}

void PlaylistController::handleMoveSongUpward() {
    logger->printMessage(Constants::MSG_ENTER_SONG_NAME);

    std::string songName;
    inputHandler->inputString(songName);

    IPlaylist* activePlaylist = playerService->getActivePlaylist();
    Song* foundSong = activePlaylist->searchSong(songName);

    if (foundSong == nullptr) 
    {
        logger->printMessage(Constants::MSG_SONG_NOT_FOUND);
    } 
    else 
    {
        if (!activePlaylist->moveSongUpward(songName)) 
        {
            logger->printMessage(Constants::MSG_CANNOT_MOVE);
            logger->printMessage(Constants::MSG_SONG_ALREADY_TOP);
        }
    }
}

void PlaylistController::handleMoveSongDownward() {
    logger->printMessage(Constants::MSG_ENTER_SONG_NAME);

    std::string songName;
    inputHandler->inputString(songName);

    IPlaylist* activePlaylist = playerService->getActivePlaylist();
    Song* foundSong = activePlaylist->searchSong(songName);

    if (foundSong == nullptr) 
    {
        logger->printMessage(Constants::MSG_SONG_NOT_FOUND);
    } 
    else 
    {
        if (!activePlaylist->moveSongDownward(songName)) 
        {
            logger->printMessage(Constants::MSG_CANNOT_MOVE);
            logger->printMessage(Constants::MSG_SONG_ALREADY_BOTTOM);
        }
    }
}

bool PlaylistController::handlePlaylistChoice(int choice) {
    bool continueMenu = true;

    switch (choice) {
        case 1:
            handlePlayPause();
            break;
        case 2:
            playerService->next();
            break;
        case 3:
            playerService->previous();
            break;
        case 4:
            handleAddSong();
            break;
        case 5:
            handleRemoveSong();
            break;
        case 6:
            handleMoveSongUpward();
            break;
        case 7:
            handleMoveSongDownward();
            break;
        case 8:
            continueMenu = false;
            break;
        default:
            logger->printMessage(Constants::MSG_INVALID_CHOICE);
    }

    return continueMenu;
}

void PlaylistController::displayPlaylistSongs() {
    IPlaylist* activePlaylist = playerService->getActivePlaylist();

    logger->printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU);
    logger->printMessage(Constants::MSG_SONGS_HEADER);

    std::list<Song>& songs = activePlaylist->getSongs();

    if (songs.empty()) 
    {
        logger->printMessage(Constants::MSG_PLAYLIST_EMPTY);
    } else 
    {
        Song* currentSong = activePlaylist->getCurrentSong();
        int index = 1;
        std::list<Song>::iterator songIterator = songs.begin();

        while (songIterator != songs.end()) 
        {
            std::string marker = (currentSong != nullptr &&
                                 songIterator->filePath == currentSong->filePath)
                                 ? Constants::MARKER : Constants::MULTIPLE_SPACES;
            logger->printMessage(marker + std::to_string(index) + Constants::FULL_STOP
            + Constants::WHITESPACE + songIterator->name);
            logger->printNewLine();
            index++;
            songIterator++;
        }
    }
}

void PlaylistController::handlePlaylistDetail() {
    bool continueMenu = true;

    while (continueMenu) 
    {
        playerService->checkAndAdvance();
        displayPlaylistSongs();
        logger->printMessage(Constants::MSG_INPUT_CHOICE);
        int choice = inputHandler->inputValue();
        continueMenu = handlePlaylistChoice(choice);
    }
}

void PlaylistController::displayAllPlaylists() {
    std::vector<std::string> playlistNames = playerService->getPlaylistNames();

    if (playlistNames.empty()) 
    {
        logger->printMessage(Constants::MSG_NO_PLAYLISTS);
    } 
    else 
    {
        logger->printMessage(Constants::MSG_PLAYLISTS_HEADER);

        int index = 1;
        std::vector<std::string>::iterator playlistIterator = playlistNames.begin();

        while (playlistIterator != playlistNames.end()) 
        {
            logger->printMessage(std::to_string(index) + Constants::FULL_STOP
            + Constants::WHITESPACE + *playlistIterator);
            logger->printNewLine();
            index++;
            playlistIterator++;
        }
    }
}

void PlaylistController::handleOpenPlaylist() {
    displayAllPlaylists();

    std::vector<std::string> playlistNames = playerService->getPlaylistNames();

    if (!playlistNames.empty()) 
    {
        logger->printMessage(Constants::MSG_ENTER_PLAYLIST_NAME);

        std::string playlistName;
        inputHandler->inputString(playlistName);

        if (playerService->selectPlaylist(playlistName)) 
        {
            handlePlaylistDetail();
        } 
        else 
        {
            logger->printMessage(Constants::MSG_PLAYLIST_NOT_FOUND);
        }
    }
}

void PlaylistController::handleCreatePlaylist() {
    logger->printMessage(Constants::MSG_ENTER_PLAYLIST_NAME);

    std::string playlistName;
    inputHandler->inputString(playlistName);

    if (playerService->createPlaylist(playlistName)) 
    {
        logger->printMessage(Constants::MSG_PLAYLIST_CREATED);
    } 
    else 
    {
        logger->printMessage(Constants::MSG_PLAYLIST_ALREADY_EXISTS);
    }
}

void PlaylistController::handleDeletePlaylist() {
    displayAllPlaylists();

    if (!playerService->getPlaylistNames().empty())
    {
        logger->printMessage(Constants::MSG_ENTER_PLAYLIST_NAME);

        std::string playlistName;
        inputHandler->inputString(playlistName);

        if (playerService->deletePlaylist(playlistName)) 
        {
            logger->printMessage(Constants::MSG_PLAYLIST_DELETED);
        } 
        else 
        {
            logger->printMessage(Constants::MSG_PLAYLIST_NOT_FOUND);
        }
    }
}

void PlaylistController::handlePlaylistMenu() {
    bool continueMenu = true;

    while (continueMenu) 
    {
        playerService->checkAndAdvance();
        logger->printMessage(Constants::MSG_PLAYLIST_MENU);
        logger->printMessage(Constants::MSG_INPUT_CHOICE);

        int choice = inputHandler->inputValue();

        switch (choice) {
            case 1:
                handleOpenPlaylist();
                break;
            case 2:
                handleCreatePlaylist();
                break;
            case 3:
                handleDeletePlaylist();
                break;
            case 4:
                continueMenu = false;
                break;
            default:
                logger->printMessage(Constants::MSG_INVALID_CHOICE);
        }
    }
}
