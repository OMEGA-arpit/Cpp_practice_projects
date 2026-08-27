#ifndef I_MUSIC_LIBRARY_H
#define I_MUSIC_LIBRARY_H

#include "Song.h"
#include <set>
#include <string>

class IMusicLibrary {
public:
    virtual const std::set<Song>& getSongs() const = 0;
    virtual const Song* findSongByTitle(const std::string& title) const = 0;

    virtual ~IMusicLibrary() = default;
};

#endif
