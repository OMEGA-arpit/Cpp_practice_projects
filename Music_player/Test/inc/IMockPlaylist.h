#ifndef I_MOCK_PLAYLIST_H
#define I_MOCK_PLAYLIST_H

#include <gmock/gmock.h>
#include "IPlaylist.h"
#include "Constants.h"

class IMockPlaylist : public IPlaylist {
public:
    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(const std::list<Song>&, getSongs, (), (const, override));
    MOCK_METHOD(Song*, getCurrentSong, (), (override));
    MOCK_METHOD(Constants::PlaybackState, getState, (), (const, override));

    MOCK_METHOD(void, setState, (Constants::PlaybackState state), (override));

    MOCK_METHOD(bool, addSong, (const Song& song), (override));
    MOCK_METHOD(bool, removeSong, (const std::string& title), (override));
    MOCK_METHOD(bool, moveSongUpward, (const std::string& title), (override));
    MOCK_METHOD(bool, moveSongDownward, (const std::string& title), (override));

    MOCK_METHOD(Song*, nextSong, (), (override));
    MOCK_METHOD(Song*, previousSong, (), (override));

    MOCK_METHOD(Song*, searchSong, (const std::string& title), (override));
};

#endif
