#ifndef SONG_H
#define SONG_H

#include <string>

struct Song {
    std::string name;
    std::string filePath;

    Song() {}

    Song(const std::string& name, const std::string& filePath)
        : name(name), filePath(filePath) {}

    bool operator<(const Song& other) const {
        return name < other.name;
    }

    bool operator==(const Song& other) const {
        return name == other.name;  
    }
};

#endif
