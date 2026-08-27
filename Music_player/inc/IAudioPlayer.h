#ifndef IAUDIO_PLAYER_H
#define IAUDIO_PLAYER_H

#include <string>
#include <functional>

/**
 * @brief Abstracts all audio playback operations.
 *
 * Implementations wrap an underlying audio engine (e.g. miniaudio).
 * Ownership of the engine is confined to the concrete class; callers
 * interact only through this interface.
 */
class IAudioPlayer {
public:
    /**
     * @brief Loads and immediately starts playing an audio file.
     * @param filePath Relative path to the .mp3 file.
     */
    virtual void play(const std::string& filePath) = 0;

    /// Pauses the currently playing sound without unloading it.
    virtual void pause() = 0;

    /// Resumes a paused sound from where it was stopped.
    virtual void resume() = 0;

    /// Stops playback and rewinds to the beginning of the track.
    virtual void stop() = 0;

    /**
     * @brief Returns whether audio is currently playing.
     * @return @c true if a sound is actively playing, @c false otherwise.
     */
    virtual bool isPlaying() = 0;

    /**
     * @brief Registers a callback invoked when the current track finishes.
     *
     * The callback fires the next time @ref checkSongEnd detects that
     * playback has completed. It is called on the same thread as
     * @ref checkSongEnd.
     *
     * @param callback Zero-argument callable; replaces any previously set callback.
     */
    virtual void setOnSongEnd(std::function<void()> callback) = 0;

    /**
     * @brief Polls the audio engine for end-of-track and fires the callback.
     *
     * Must be called periodically from the main application loop to detect
     * when a track has finished playing naturally.
     */
    virtual void checkSongEnd() = 0;

    virtual ~IAudioPlayer() {}
};

#endif
