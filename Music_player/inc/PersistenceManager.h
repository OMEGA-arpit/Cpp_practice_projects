#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include "IPersistenceManager.h"
#include "Constants.h"
#include "ILogger.h"
#include <string>
#include <fstream>

class PersistenceManager : public IPersistenceManager {
    ILogger* logger;
    std::string filePath;

    void savePlaylist(std::ofstream& file, const std::string& playlistName, IPlaylist* playlist);

    void addSongFromLine(const std::string& line,
                         const std::string& currentPlaylistName,
                         std::map<std::string, IPlaylist*>& playlists);


    void processLine(const std::string& line,
                     std::string& currentPlaylistName,
                     std::map<std::string, IPlaylist*>& playlists,
                     IPlaylistFactory* playlistFactory);

public:
    PersistenceManager(ILogger* logger, const std::string& filePath = Constants::PLAYLIST_FILE_PATH);

    void savePlaylists(std::map<std::string, IPlaylist*>& playlists) override;
    void loadPlaylists(std::map<std::string, IPlaylist*>& playlists, IPlaylistFactory* playlistFactory) override;
};

#endif
