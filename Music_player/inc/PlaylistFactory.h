#ifndef PLAYLIST_FACTORY_H
#define PLAYLIST_FACTORY_H

#include "IPlaylistFactory.h"
#include "Playlist.h"

class PlaylistFactory : public IPlaylistFactory {
public:
    IPlaylist* create(const std::string& playlistName) override {
        return new Playlist(playlistName);
    }
};

#endif
