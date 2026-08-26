#ifndef I_MOCK_PLAYER_SERVICE_H
#define I_MOCK_PLAYER_SERVICE_H

#include <gmock/gmock.h>
#include "IPlayerService.h"

class IMockPlayerService : public IPlayerService {
public:
    MOCK_METHOD(const std::set<Song>&, getAllSongs, (), (override));
    MOCK_METHOD(const Song*, searchSong, (const std::string& title), (override));

    MOCK_METHOD(bool, playSong, (const Song& song), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, resume, (), (override));
    MOCK_METHOD(void, next, (), (override));
    MOCK_METHOD(void, previous, (), (override));
    MOCK_METHOD(void, checkAndAdvance, (), (override));

    MOCK_METHOD(bool, createPlaylist, (const std::string& playlistName), (override));
    MOCK_METHOD(bool, deletePlaylist, (const std::string& playlistName), (override));
    MOCK_METHOD(bool, selectPlaylist, (const std::string& playlistName), (override));
    MOCK_METHOD(std::vector<std::string>, getPlaylistNames, (), (override));
    MOCK_METHOD(IPlaylist*, getActivePlaylist, (), (override));
    MOCK_METHOD(bool, isPlaying, (), (override));

    MOCK_METHOD(void, loadPlaylists, (), (override));
    MOCK_METHOD(void, savePlaylists, (), (override));
};

#endif
