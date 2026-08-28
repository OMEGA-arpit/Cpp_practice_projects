#ifndef SONG_H
#define SONG_H

#include <string>

/**
 * @brief Plain data type representing a single audio track.
 *
 * Used as a value type throughout the system. The set ordering and
 * duplicate-detection in Playlist are both based on @p filePath, not @p name.
 */
struct Song {
    std::string name;      ///< Display name derived from the filename stem.
    std::string filePath;  ///< Relative path to the .mp3 file on disk.

    Song() = default;

    /**
     * @brief Constructs a Song with the given name and file path.
     * @param name     Display name (typically the filename without extension).
     * @param filePath Path to the audio file relative to the working directory.
     */
    Song(const std::string& name, const std::string& filePath)
        : name(name), filePath(filePath) {}

    /// Orders songs alphabetically by name. Used by std::set<Song>.
    bool operator<(const Song& other) const noexcept {
        return name < other.name;
    }

    /// Two songs are equal only when both name AND filePath match.
    bool operator==(const Song& other) const noexcept {
        return name == other.name && filePath == other.filePath;
    }
};

#endif
