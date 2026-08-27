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

    std::list<Song>::iterator findByTitle(const std::string& title);

public:
    Playlist() = default;

    explicit Playlist(const std::string& name);

    std::string getName() const override;
    const std::list<Song>& getSongs() const override;
    Song* getCurrentSong() override;
    Constants::PlaybackState getState() const override;

    void setState(Constants::PlaybackState state) override;

    [[nodiscard]] bool addSong(const Song& song) override;
    [[nodiscard]] bool removeSong(const std::string& title) override;
    [[nodiscard]] bool moveSongUpward(const std::string& title) override;
    [[nodiscard]] bool moveSongDownward(const std::string& title) override;

    Song* nextSong() override;
    Song* previousSong() override;

    Song* searchSong(const std::string& title) override;
};

#endif
