#ifndef PLAYER_SERVICE_H
#define PLAYER_SERVICE_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include "IPlayerService.h"
#include "IMusicLibrary.h"
#include "IAudioPlayer.h"
#include "IPersistenceManager.h"
#include "IPlaylistFactory.h"
#include "IPlaylist.h"

class PlayerService : public IPlayerService {
    std::unique_ptr<IMusicLibrary> musicLibrary;
    std::unique_ptr<IAudioPlayer> audioPlayer;
    std::unique_ptr<IPersistenceManager> persistenceManager;
    std::unique_ptr<IPlaylistFactory> playlistFactory;
    std::map<std::string, std::unique_ptr<IPlaylist>> playlists;
    std::string activePlaylistName;

public:
    PlayerService(std::unique_ptr<IMusicLibrary> musicLibrary,
                  std::unique_ptr<IAudioPlayer> audioPlayer,
                  std::unique_ptr<IPersistenceManager> persistenceManager,
                  std::unique_ptr<IPlaylistFactory> playlistFactory);

    const std::set<Song>& getAllSongs() const override;
    const Song* searchSong(const std::string& songName) const override;

    bool playSong(const Song& song) override;
    void pause() override;
    void resume() override;
    void next() override;
    void previous() override;
    void checkAndAdvance() override;
    bool isPlaying() const override;

    bool createPlaylist(const std::string& playlistName) override;
    bool deletePlaylist(const std::string& playlistName) override;
    bool selectPlaylist(const std::string& playlistName) override;
    std::vector<std::string> getPlaylistNames() const override;
    IPlaylist* getActivePlaylist() override;

    void loadPlaylists() override;
    void savePlaylists() override;
};

#endif
