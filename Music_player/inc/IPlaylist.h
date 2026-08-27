#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <string>
#include <list>
#include "Song.h"
#include "Constants.h"

class IPlaylist {
public:
    virtual std::string getName() const = 0;
    virtual const std::list<Song>& getSongs() const = 0;
    virtual Song* getCurrentSong() = 0;
    virtual Constants::PlaybackState getState() const = 0;

    virtual void setState(Constants::PlaybackState state) = 0;

    [[nodiscard]] virtual bool addSong(const Song& song) = 0;
    [[nodiscard]] virtual bool removeSong(const std::string& title) = 0;
    [[nodiscard]] virtual bool moveSongUpward(const std::string& title) = 0;
    [[nodiscard]] virtual bool moveSongDownward(const std::string& title) = 0;

    virtual Song* nextSong() = 0;
    virtual Song* previousSong() = 0;

    virtual Song* searchSong(const std::string& title) = 0;

    virtual ~IPlaylist() = default;
};

#endif
