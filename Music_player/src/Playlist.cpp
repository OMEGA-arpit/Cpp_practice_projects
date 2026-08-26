#include "Playlist.h"
#include <algorithm>

Playlist::Playlist(const std::string& playlistName)
    : name(playlistName), state(Constants::PlaybackState::STOPPED), isInitialized(false) {}

std::string Playlist::getName() {
    return name;
}

std::list<Song>& Playlist::getSongs() {
    return songs;
}

Song* Playlist::getCurrentSong() {
    Song* song = nullptr;

    if (isInitialized && !songs.empty()) 
    {
        song = &(*currentSong);
    }

    return song;
}

Constants::PlaybackState Playlist::getState() {
    return state;
}

void Playlist::setState(Constants::PlaybackState newState) {
    state = newState;
}

bool Playlist::addSong(const Song& songToAdd) {
    bool isDuplicate = false;

    for (const Song& existingSong : songs) 
    {
        if (existingSong.filePath == songToAdd.filePath) 
        {
            isDuplicate = true;
            break;
        }
    }

    if (!isDuplicate) 
    {
        songs.push_back(songToAdd);

        if (!isInitialized) 
        {
            currentSong = songs.begin();
            isInitialized = true;
        }
    }

    return !isDuplicate;
}

bool Playlist::removeSong(const std::string& songTitle) {
    std::list<Song>::iterator songIterator = findByTitle(songTitle);
    bool songExists = (songIterator != songs.end());

    if (songExists) 
    {
        if (isInitialized && songIterator == currentSong) 
        {
            if (songs.size() == 1) 
            {
                isInitialized = false;
            } 
            else 
            {
                std::list<Song>::iterator nextIterator = std::next(songIterator);
                currentSong = (nextIterator == songs.end()) ? std::prev(songIterator) : nextIterator;
            }
        }

        songs.erase(songIterator);

        if (songs.empty()) 
        {
            isInitialized = false;
            state = Constants::PlaybackState::STOPPED;
        }
    }

    return songExists;
}

bool Playlist::moveSongUpward(const std::string& songTitle) {
    std::list<Song>::iterator songIterator = findByTitle(songTitle);
    bool canMoveUp = (songIterator != songs.end() && songIterator != songs.begin());

    if (canMoveUp) 
    {
        songs.splice(std::prev(songIterator), songs, songIterator);
    }

    return canMoveUp;
}

bool Playlist::moveSongDownward(const std::string& songTitle) {
    std::list<Song>::iterator songIterator = findByTitle(songTitle);
    bool songExists = (songIterator != songs.end());
    bool canMoveDown = false;

    if (songExists) 
    {
        std::list<Song>::iterator nextIterator = std::next(songIterator);
        canMoveDown = (nextIterator != songs.end());

        if (canMoveDown) 
        {
            songs.splice(songIterator, songs, nextIterator);
        }
    }

    return canMoveDown;
}

Song* Playlist::nextSong() {
    Song* nextSong = nullptr;

    if (isInitialized && !songs.empty()) 
    {
        currentSong++;
        if (currentSong == songs.end()) 
        {
            currentSong = songs.begin();
        }
        nextSong = &(*currentSong);
    }

    return nextSong;
}

Song* Playlist::previousSong() {
    Song* previousSong = nullptr;

    if (isInitialized && !songs.empty()) 
    {
        if (currentSong == songs.begin()) 
        {
            currentSong = std::prev(songs.end());
        } else 
        {
            currentSong--;
        }
        previousSong = &(*currentSong);
    }

    return previousSong;
}

Song* Playlist::searchSong(const std::string& songTitle) {
    std::list<Song>::iterator songIterator = findByTitle(songTitle);
    Song* foundSong = nullptr;

    if (songIterator != songs.end()) 
    {
        foundSong = &(*songIterator);
    }

    return foundSong;
}

std::list<Song>::iterator Playlist::findByTitle(const std::string& songTitle) {
    return std::find_if(songs.begin(), songs.end(),
        [&songTitle](const Song& song) { return song.name == songTitle; });
}
