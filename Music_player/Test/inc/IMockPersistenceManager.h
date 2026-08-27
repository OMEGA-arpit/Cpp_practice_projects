#ifndef I_MOCK_PERSISTENCE_MANAGER_H
#define I_MOCK_PERSISTENCE_MANAGER_H

#include <memory>
#include <gmock/gmock.h>
#include "IPersistenceManager.h"

class IMockPersistenceManager : public IPersistenceManager {
public:
    MOCK_METHOD(void, savePlaylists,
                ((const std::map<std::string, std::unique_ptr<IPlaylist>>&) playlists),
                (override));
    MOCK_METHOD(void, loadPlaylists,
                ((std::map<std::string, std::unique_ptr<IPlaylist>>&) playlists,
                 IPlaylistFactory* playlistFactory),
                (override));
};

#endif
