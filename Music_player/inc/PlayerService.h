#ifndef PLAYER_SERVICE_H
#define PLAYER_SERVICE_H

#include <map>
#include <vector>
#include <string>
#include "IPlayerService.h"
#include "IMusicLibrary.h"
#include "IAudioPlayer.h"
#include "IPersistenceManager.h"
#include "IPlaylistFactory.h"
#include "IPlaylist.h"

class PlayerService : public IPlayerService {
    IMusicLibrary* musicLibrary;
    IAudioPlayer* audioPlayer;
    IPersistenceManager* persistenceManager;
    IPlaylistFactory* playlistFactory;
    std::map<std::string, IPlaylist*> playlists;
    std::string activePlaylistName;

public:
    PlayerService(IMusicLibrary* musicLibrary,
                  IAudioPlayer* audioPlayer,
                  IPersistenceManager* persistenceManager,
                  IPlaylistFactory* playlistFactory);

    const std::set<Song>& getAllSongs() override;
    const Song* searchSong(const std::string& songName) override;

    bool playSong(const Song& song) override;
    void pause() override;
    void resume() override;
    void next() override;
    void previous() override;
    void checkAndAdvance() override;
    bool isPlaying() override;

    bool createPlaylist(const std::string& playlistName) override;
    bool deletePlaylist(const std::string& playlistName) override;
    bool selectPlaylist(const std::string& playlistName) override;
    std::vector<std::string> getPlaylistNames() override;
    IPlaylist* getActivePlaylist() override;

    void loadPlaylists() override;
    void savePlaylists() override;

    ~PlayerService();
};

#endif
