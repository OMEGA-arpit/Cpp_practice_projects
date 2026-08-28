#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Constants.h"
#include "IMusicLibrary.h"
#include "Song.h"
#include <set>
#include <string>

class MusicLibrary : public IMusicLibrary {
    std::set<Song> songs;

    bool loadSongsFromFolder(const std::string& folderPath);

public:
    explicit MusicLibrary(const std::string& folderPath = Constants::SONGS_FOLDER_PATH) {
        loadSongsFromFolder(folderPath);
    }

    const std::set<Song>& getSongs() const override {
        return songs;
    }

    const Song* findSongByTitle(const std::string& title) const override;
};

#endif
