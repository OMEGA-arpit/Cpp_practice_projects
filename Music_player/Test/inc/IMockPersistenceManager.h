#ifndef I_MOCK_PERSISTENCE_MANAGER_H
#define I_MOCK_PERSISTENCE_MANAGER_H

#include <gmock/gmock.h>
#include "IPersistenceManager.h"

class IMockPersistenceManager : public IPersistenceManager {
public:
    MOCK_METHOD(void, savePlaylists, ((std::map<std::string, IPlaylist*>&) playlists), (override));
    MOCK_METHOD(void, loadPlaylists, ((std::map<std::string, IPlaylist*>&) playlists, 
    IPlaylistFactory* playlistFactory),(override));
};

#endif
