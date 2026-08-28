#ifndef I_MUSIC_LIBRARY_H
#define I_MUSIC_LIBRARY_H

#include "Song.h"
#include <set>
#include <string>

/**
 * @brief Provides read-only access to all songs discovered on disk.
 *
 * The library is populated once at startup by scanning a configured folder
 * (and its subdirectories) for .mp3 files. After initialisation the
 * collection is immutable for the lifetime of the application.
 */
class IMusicLibrary {
public:
    /**
     * @brief Returns the full set of songs loaded from disk.
     *
     * The set is ordered alphabetically by song name (@ref Song::operator<).
     *
     * @return Const reference to the internal song set.
     */
    virtual const std::set<Song>& getSongs() const = 0;

    /**
     * @brief Searches for a song by its display name.
     * @param title Exact display name to search for (case-sensitive).
     * @return Pointer to the found Song, or @c nullptr if not found.
     */
    virtual const Song* findSongByTitle(const std::string& title) const = 0;

    virtual ~IMusicLibrary() = default;
};

#endif
