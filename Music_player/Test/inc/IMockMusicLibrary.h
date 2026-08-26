#ifndef I_MOCK_MUSIC_LIBRARY_H
#define I_MOCK_MUSIC_LIBRARY_H

#include <gmock/gmock.h>
#include "IMusicLibrary.h"

class IMockMusicLibrary : public IMusicLibrary {
public:
    MOCK_METHOD(std::set<Song>&, getSongs, (), (override));
    MOCK_METHOD(const Song*, findSongByTitle, (const std::string& title), (override));
};

#endif
