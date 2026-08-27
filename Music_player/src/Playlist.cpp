#include "Playlist.h"
#include <algorithm>

Playlist::Playlist(const std::string& playlistName)
    : name(playlistName), state(Constants::PlaybackState::STOPPED) {}

std::string Playlist::getName() const {
    return name;
}

const std::list<Song>& Playlist::getSongs() const {
    return songs;
}

Song* Playlist::getCurrentSong() {
    if (songs.empty()) {
        return nullptr;
    }
    return &(*currentSong);
}

Constants::PlaybackState Playlist::getState() const {
    return state;
}

void Playlist::setState(Constants::PlaybackState newState) {
    state = newState;
}

bool Playlist::addSong(const Song& songToAdd) {
    for (const Song& existingSong : songs) 
    {
        if (existingSong.filePath == songToAdd.filePath) 
        {
            return false;
        }
    }

    songs.push_back(songToAdd);

    if (songs.size() == 1) 
    {
        currentSong = songs.begin();
    }

    return true;
}

bool Playlist::removeSong(const std::string& songTitle) {
    auto songIterator = findByTitle(songTitle);
    bool songExists = (songIterator != songs.end());

    if (songExists) 
    {
        if (!songs.empty() && songIterator == currentSong) 
        {
            if (songs.size() == 1) 
            {
                songs.erase(songIterator);
                state = Constants::PlaybackState::STOPPED;
                return true;
            } 
            else 
            {
                auto nextIterator = std::next(songIterator);
                currentSong = (nextIterator == songs.end()) ? std::prev(songIterator) : nextIterator;
            }
        }

        songs.erase(songIterator);
    }

    return songExists;
}

bool Playlist::moveSongUpward(const std::string& songTitle) {
    auto songIterator = findByTitle(songTitle);
    bool canMoveUp = (songIterator != songs.end() && songIterator != songs.begin());

    if (canMoveUp) 
    {
        songs.splice(std::prev(songIterator), songs, songIterator);
    }

    return canMoveUp;
}

bool Playlist::moveSongDownward(const std::string& songTitle) {
    auto songIterator = findByTitle(songTitle);
    bool songExists = (songIterator != songs.end());
    bool canMoveDown = false;

    if (songExists) 
    {
        auto nextIterator = std::next(songIterator);
        canMoveDown = (nextIterator != songs.end());

        if (canMoveDown) 
        {
            songs.splice(songIterator, songs, nextIterator);
        }
    }

    return canMoveDown;
}

Song* Playlist::nextSong() {
    if (songs.empty()) 
    {
        return nullptr;
    }

    ++currentSong;
    if (currentSong == songs.end()) 
    {
        currentSong = songs.begin();
    }
    return &(*currentSong);
}

Song* Playlist::previousSong() {
    if (songs.empty()) 
    {
        return nullptr;
    }

    if (currentSong == songs.begin()) 
    {
        currentSong = std::prev(songs.end());
    } else 
    {
        --currentSong;
    }
    return &(*currentSong);
}

Song* Playlist::searchSong(const std::string& songTitle) {
    auto songIterator = findByTitle(songTitle);

    if (songIterator == songs.end()) 
    {
        return nullptr;
    }
    return &(*songIterator);
}

std::list<Song>::iterator Playlist::findByTitle(const std::string& songTitle) {
    return std::find_if(songs.begin(), songs.end(),
        [&songTitle](const Song& song) { return song.name == songTitle; });
}
