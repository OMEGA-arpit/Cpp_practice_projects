#ifndef IPERSISTENCE_MANAGER_H
#define IPERSISTENCE_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include "IPlaylist.h"
#include "IPlaylistFactory.h"

/**
 * @brief Persists and restores the playlist collection across sessions.
 *
 * The default implementation stores playlists in a plain-text file using
 * the format:
 * @code
 * PLAYLIST:<name>
 * <song_name>|<file_path>
 * ...
 * @endcode
 */
class IPersistenceManager {
public:
    /**
     * @brief Serialises all playlists to the backing store.
     * @param playlists Map of playlist name to owned playlist object.
     */
    virtual void savePlaylists(const std::map<std::string, std::unique_ptr<IPlaylist>>& playlists) = 0;

    /**
     * @brief Deserialises playlists from the backing store into @p playlists.
     *
     * Existing entries in @p playlists are not cleared first; any playlist names
     * present in the file that already exist in the map will be overwritten.
     *
     * @param[out] playlists Map to populate with the loaded playlists.
     * @param      playlistFactory Factory used to create each playlist instance.
     */
    virtual void loadPlaylists(std::map<std::string, std::unique_ptr<IPlaylist>>& playlists,
                               IPlaylistFactory* playlistFactory) = 0;

    virtual ~IPersistenceManager() = default;
};

#endif
