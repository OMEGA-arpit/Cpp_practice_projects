#ifndef PLAYLIST_FACTORY_H
#define PLAYLIST_FACTORY_H

#include <memory>
#include "IPlaylistFactory.h"
#include "Playlist.h"

class PlaylistFactory : public IPlaylistFactory {
public:
    std::unique_ptr<IPlaylist> create(const std::string& playlistName) override {
        return std::make_unique<Playlist>(playlistName);
    }
};

#endif
