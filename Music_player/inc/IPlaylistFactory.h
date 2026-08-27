#ifndef IPLAYLIST_FACTORY_H
#define IPLAYLIST_FACTORY_H

#include <memory>
#include <string>
#include "IPlaylist.h"

class IPlaylistFactory {
public:
    virtual std::unique_ptr<IPlaylist> create(const std::string& playlistName) = 0;

    virtual ~IPlaylistFactory() = default;
};

#endif
