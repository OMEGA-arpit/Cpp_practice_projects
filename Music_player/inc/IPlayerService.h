#ifndef IPLAYER_SERVICE_H
#define IPLAYER_SERVICE_H

#include <set>
#include <map>
#include <string>
#include "Song.h"
#include "IPlaylist.h"

class IPlayerService {
public:
    virtual const std::set<Song>& getAllSongs() = 0;
    virtual const Song* searchSong(const std::string& title) = 0;

    virtual bool playSong(const Song& song) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void checkAndAdvance() = 0;
    virtual bool isPlaying() = 0;

    virtual bool createPlaylist(const std::string& playlistName) = 0;
    virtual bool deletePlaylist(const std::string& playlistName) = 0;
    virtual bool selectPlaylist(const std::string& playlistName) = 0;
    virtual std::vector<std::string> getPlaylistNames() = 0;
    virtual IPlaylist* getActivePlaylist() = 0;

    virtual void loadPlaylists() = 0;
    virtual void savePlaylists() = 0;

    virtual ~IPlayerService() {};
};

#endif
