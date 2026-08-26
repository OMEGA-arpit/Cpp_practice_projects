#include "MusicLibrary.h"
#include "Constants.h"
#include <filesystem>

bool MusicLibrary::loadSongsFromFolder(const std::string& folderPath) {
    bool areSongsLoaded = true;
    if (!std::filesystem::exists(folderPath)) 
    {
        areSongsLoaded = false;
    }
    else
    {
        for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(folderPath)) 
        {
            if (entry.is_regular_file() && entry.path().extension() == Constants::MP3_EXTENSION) 
            {
                std::string name = entry.path().stem().string();
                std::string path = entry.path().string();
                songs.emplace(name, path);
            }
        }
    }

    return areSongsLoaded;
}

const Song* MusicLibrary::findSongByTitle(const std::string& title) {
    Song searchKey(title, Constants::EMPTY_STRING);

    const Song* foundSong = nullptr;

    std::set<Song>::iterator songIterator = songs.find(searchKey);

    if (songIterator != songs.end()) 
    {
        foundSong = &(*songIterator);
    }

    return foundSong;
}
