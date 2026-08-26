#ifndef IPLAYLIST_H
#define IPLAYLIST_H

#include <string>
#include <list>
#include "Song.h"
#include "Constants.h"

class IPlaylist {
public:
    virtual std::string getName() = 0;
    virtual std::list<Song>& getSongs() = 0;
    virtual Song* getCurrentSong() = 0;
    virtual Constants::PlaybackState getState() = 0;

    virtual void setState(Constants::PlaybackState state) = 0;

    virtual bool addSong(const Song& song) = 0;
    virtual bool removeSong(const std::string& title) = 0;
    virtual bool moveSongUpward(const std::string& title) = 0;
    virtual bool moveSongDownward(const std::string& title) = 0;

    virtual Song* nextSong() = 0;
    virtual Song* previousSong() = 0;

    virtual Song* searchSong(const std::string& title) = 0;

    virtual ~IPlaylist() {};
};

#endif
