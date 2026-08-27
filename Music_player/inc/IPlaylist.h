#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <string>
#include <list>
#include "Song.h"
#include "Constants.h"

/**
 * @brief Represents an ordered, named collection of songs.
 *
 * A playlist maintains a "current song" cursor that supports circular
 * navigation: calling @ref nextSong on the last song wraps back to the
 * first, and @ref previousSong on the first wraps to the last.
 *
 * Duplicate detection is based on @p Song::filePath, not the display name.
 */
class IPlaylist {
public:
    /// @return The playlist's display name.
    virtual std::string getName() const = 0;

    /// @return Const reference to the internal ordered song list.
    virtual const std::list<Song>& getSongs() const = 0;

    /**
     * @brief Returns a pointer to the currently selected song.
     * @return Pointer to the current Song, or @c nullptr if the playlist is empty.
     */
    virtual Song* getCurrentSong() = 0;

    /// @return The current playback state (STOPPED, PLAYING, or PAUSED).
    virtual Constants::PlaybackState getState() const = 0;

    /// @param state The new playback state to record.
    virtual void setState(Constants::PlaybackState state) = 0;

    /**
     * @brief Appends a song to the end of the playlist if it is not already present.
     *
     * Uniqueness is determined by @p Song::filePath. If the playlist was
     * empty, the new song becomes the current song.
     *
     * @param song The song to add.
     * @return @c true if the song was added, @c false if it was a duplicate.
     */
    [[nodiscard]] virtual bool addSong(const Song& song) = 0;

    /**
     * @brief Removes the song with the given title from the playlist.
     *
     * If the removed song was the current song, the cursor advances to the
     * next song (or wraps to the previous if at the end).
     *
     * @param title Display name of the song to remove.
     * @return @c true if a matching song was found and removed, @c false otherwise.
     */
    [[nodiscard]] virtual bool removeSong(const std::string& title) = 0;

    /**
     * @brief Moves the named song one position earlier in the list.
     * @param title Display name of the song to move.
     * @return @c true if the move succeeded, @c false if the song is already first.
     */
    [[nodiscard]] virtual bool moveSongUpward(const std::string& title) = 0;

    /**
     * @brief Moves the named song one position later in the list.
     * @param title Display name of the song to move.
     * @return @c true if the move succeeded, @c false if the song is already last.
     */
    [[nodiscard]] virtual bool moveSongDownward(const std::string& title) = 0;

    /**
     * @brief Advances the current-song cursor by one position, wrapping at the end.
     * @return Pointer to the new current Song, or @c nullptr if the playlist is empty.
     */
    virtual Song* nextSong() = 0;

    /**
     * @brief Moves the current-song cursor back one position, wrapping at the start.
     * @return Pointer to the new current Song, or @c nullptr if the playlist is empty.
     */
    virtual Song* previousSong() = 0;

    /**
     * @brief Finds a song by its display name.
     * @param title Exact display name to search for.
     * @return Pointer to the found Song, or @c nullptr if not found.
     */
    virtual Song* searchSong(const std::string& title) = 0;

    virtual ~IPlaylist() = default;
};

#endif
