#ifndef SONG_H
#define SONG_H

#include <string>

struct Song {
    std::string name;
    std::string filePath;

    Song() = default;

    Song(const std::string& name, const std::string& filePath)
        : name(name), filePath(filePath) {}

    bool operator<(const Song& other) const noexcept {
        return name < other.name;
    }

    bool operator==(const Song& other) const noexcept {
        return name == other.name && filePath == other.filePath;
    }
};

#endif
