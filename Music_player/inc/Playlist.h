#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <list>
#include <string>
#include "IPlaylist.h"
#include "Song.h"

class Playlist : public IPlaylist {
    std::string name;
    std::list<Song> songs;
    std::list<Song>::iterator currentSong;
    Constants::PlaybackState state;
    bool isInitialized;

    std::list<Song>::iterator findByTitle(const std::string& title);

public:
    Playlist() {}
    
    Playlist(const std::string& name);

    std::string getName() override;
    std::list<Song>& getSongs() override;
    Song* getCurrentSong() override;
    Constants::PlaybackState getState() override;

    void setState(Constants::PlaybackState state) override;

    bool addSong(const Song& song) override;
    bool removeSong(const std::string& title) override;
    bool moveSongUpward(const std::string& title) override;
    bool moveSongDownward(const std::string& title) override;

    Song* nextSong() override;
    Song* previousSong() override;

    Song* searchSong(const std::string& title) override;
};

#endif
