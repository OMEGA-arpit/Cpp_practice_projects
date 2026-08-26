#include "PersistenceManager.h"
#include "Constants.h"
#include <fstream>

PersistenceManager::PersistenceManager(ILogger* logger, const std::string& filePath)
    : logger(logger), filePath(filePath) {}

void PersistenceManager::savePlaylist(std::ofstream& file, const std::string& playlistName, IPlaylist* playlist) {
    file << Constants::PLAYLIST_PREFIX << playlistName << Constants::NEW_LINE;

    std::list<Song>& songs = playlist->getSongs();
    std::list<Song>::iterator songIterator = songs.begin();

    while (songIterator != songs.end()) 
    {
        file << songIterator->name << Constants::SEPARATOR << songIterator->filePath << Constants::NEW_LINE;
        songIterator++;
    }
}

void PersistenceManager::savePlaylists(std::map<std::string, IPlaylist*>& playlists) {
    std::ofstream file(filePath);

    if (!file.is_open()) 
    {
        logger->printMessage(Constants::MSG_FILE_SAVE_FAILED + filePath);
    } 
    else 
    {
        std::map<std::string, IPlaylist*>::iterator playlistIterator = playlists.begin();

        while (playlistIterator != playlists.end()) 
        {
            savePlaylist(file, playlistIterator->first, playlistIterator->second);
            playlistIterator++;
        }
    }
}

void PersistenceManager::addSongFromLine(const std::string& line,
                                         const std::string& currentPlaylistName,
                                         std::map<std::string, IPlaylist*>& playlists) {
    size_t separatorPosition = line.find(Constants::SEPARATOR);
    bool separatorFound = (separatorPosition != std::string::npos);

    if (separatorFound) 
    {
        Song song;
        song.name = line.substr(0, separatorPosition);
        song.filePath = line.substr(separatorPosition + 1);
        playlists[currentPlaylistName]->addSong(song);
    }
}

void PersistenceManager::processLine(const std::string& line,
                                     std::string& currentPlaylistName,
                                     std::map<std::string, IPlaylist*>& playlists,
                                     IPlaylistFactory* playlistFactory) {
    bool isPlaylistLine = (line.rfind(Constants::PLAYLIST_PREFIX, 0) == 0);

    if (isPlaylistLine) 
    {
        currentPlaylistName = line.substr(Constants::PLAYLIST_PREFIX.size());
        playlists[currentPlaylistName] = playlistFactory->create(currentPlaylistName);
    } 
    else if (!currentPlaylistName.empty() && !line.empty()) 
    {
        addSongFromLine(line, currentPlaylistName, playlists);
    }
}

void PersistenceManager::loadPlaylists(std::map<std::string, IPlaylist*>& playlists, IPlaylistFactory* playlistFactory) {
    std::ifstream file(filePath);

    if (!file.is_open()) 
    {
        logger->printMessage(Constants::MSG_FILE_LOAD_FAILED + filePath);
    } 
    else 
    {
        std::string line;
        std::string currentPlaylistName = Constants::EMPTY_STRING;

        while (std::getline(file, line)) 
        {
            processLine(line, currentPlaylistName, playlists, playlistFactory);
        }
    }
}
