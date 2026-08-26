#ifndef I_MUSIC_LIBRARY_H
#define I_MUSIC_LIBRARY_H

#include "Song.h"
#include <set>
#include <string>

class IMusicLibrary {
public: 
    virtual std::set<Song>& getSongs() = 0;
    virtual const Song* findSongByTitle(const std::string& title) = 0;
};

#endif
