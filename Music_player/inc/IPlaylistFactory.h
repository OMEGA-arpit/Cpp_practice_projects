#ifndef IPLAYLIST_FACTORY_H
#define IPLAYLIST_FACTORY_H

#include <memory>
#include <string>
#include "IPlaylist.h"

/**
 * @brief Factory for creating Playlist instances.
 *
 * Decouples playlist creation from the classes that manage playlists
 * (PlayerService, PersistenceManager), enabling substitution in tests.
 */
class IPlaylistFactory {
public:
    /**
     * @brief Creates a new, empty playlist with the given name.
     * @param playlistName The display name for the new playlist.
     * @return Owning pointer to the newly created playlist.
     */
    virtual std::unique_ptr<IPlaylist> create(const std::string& playlistName) = 0;

    virtual ~IPlaylistFactory() = default;
};

#endif
