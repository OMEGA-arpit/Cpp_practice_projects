#ifndef IPLAYER_SERVICE_H
#define IPLAYER_SERVICE_H

#include <set>
#include <map>
#include <string>
#include "Song.h"
#include "IPlaylist.h"

/**
 * @brief Central facade that coordinates all playback and playlist operations.
 *
 * PlayerService aggregates the music library, audio player, persistence
 * manager, and playlist factory. It is the single point of contact for
 * the UI layer (MusicApplication, PlaylistController).
 *
 * Playlist auto-advance: when the audio engine finishes a track it calls
 * @ref next automatically via the on-song-end callback.
 */
class IPlayerService {
public:
    // ── Library queries ────────────────────────────────────────────────────

    /// @return Const reference to the full song set loaded from disk.
    virtual const std::set<Song>& getAllSongs() const = 0;

    /**
     * @brief Searches the music library for a song by name.
     * @param title Exact display name (case-sensitive).
     * @return Pointer to the matching Song, or @c nullptr if not found.
     */
    virtual const Song* searchSong(const std::string& title) const = 0;

    // ── Playback control ───────────────────────────────────────────────────

    /**
     * @brief Stops the current track and begins playing @p song.
     * @param song Song to play; its @p filePath is passed to the audio engine.
     * @return @c true if the audio engine reported that playback started.
     */
    virtual bool playSong(const Song& song) = 0;

    /// Pauses the currently playing track.
    virtual void pause() = 0;

    /// Resumes a paused track.
    virtual void resume() = 0;

    /**
     * @brief Advances to the next song in the active playlist.
     *
     * Called automatically by the on-song-end callback. Does nothing if
     * no playlist is currently active.
     */
    virtual void next() = 0;

    /**
     * @brief Returns to the previous song in the active playlist.
     *
     * Does nothing if no playlist is currently active.
     */
    virtual void previous() = 0;

    /**
     * @brief Polls the audio engine for end-of-track detection.
     *
     * Must be called from the main menu loop each iteration to allow the
     * on-song-end callback to fire without a dedicated audio thread.
     */
    virtual void checkAndAdvance() = 0;

    /// @return @c true if audio is currently playing.
    virtual bool isPlaying() const = 0;

    // ── Playlist management ────────────────────────────────────────────────

    /**
     * @brief Creates a new empty playlist with the given name.
     * @param playlistName Name for the new playlist (must be unique).
     * @return @c true if created, @c false if a playlist with that name already exists.
     */
    virtual bool createPlaylist(const std::string& playlistName) = 0;

    /**
     * @brief Deletes the named playlist.
     * @param playlistName Name of the playlist to remove.
     * @return @c true if found and deleted, @c false if not found.
     */
    virtual bool deletePlaylist(const std::string& playlistName) = 0;

    /**
     * @brief Sets the named playlist as the active (currently open) playlist.
     * @param playlistName Name of the playlist to activate.
     * @return @c true if found and selected, @c false if not found.
     */
    virtual bool selectPlaylist(const std::string& playlistName) = 0;

    /// @return Names of all playlists in alphabetical order.
    virtual std::vector<std::string> getPlaylistNames() const = 0;

    /**
     * @brief Returns a non-owning pointer to the currently active playlist.
     * @return Pointer to the active IPlaylist, or @c nullptr if none is selected.
     */
    virtual IPlaylist* getActivePlaylist() = 0;

    // ── Persistence ────────────────────────────────────────────────────────

    /// Loads playlists from the backing store into memory.
    virtual void loadPlaylists() = 0;

    /// Serialises all in-memory playlists to the backing store.
    virtual void savePlaylists() = 0;

    virtual ~IPlayerService() = default;
};

#endif
