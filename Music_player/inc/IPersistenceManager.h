#ifndef IPERSISTENCE_MANAGER_H
#define IPERSISTENCE_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include "IPlaylist.h"
#include "IPlaylistFactory.h"

class IPersistenceManager {
public:
    virtual void savePlaylists(const std::map<std::string, std::unique_ptr<IPlaylist>>& playlists) = 0;
    virtual void loadPlaylists(std::map<std::string, std::unique_ptr<IPlaylist>>& playlists,
                               IPlaylistFactory* playlistFactory) = 0;

    virtual ~IPersistenceManager() = default;
};

#endif
