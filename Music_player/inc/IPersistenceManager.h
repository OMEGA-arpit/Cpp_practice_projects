#ifndef IPERSISTENCE_MANAGER_H
#define IPERSISTENCE_MANAGER_H

#include <map>
#include <string>
#include "IPlaylist.h"
#include "IPlaylistFactory.h"

class IPersistenceManager {
public:
    virtual void savePlaylists(std::map<std::string, IPlaylist*>& playlists) = 0;
    virtual void loadPlaylists(std::map<std::string, IPlaylist*>& playlists, IPlaylistFactory* playlistFactory) = 0;

    virtual ~IPersistenceManager() {};
};

#endif
