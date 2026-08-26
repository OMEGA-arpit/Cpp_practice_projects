#ifndef IPLAYLIST_FACTORY_H
#define IPLAYLIST_FACTORY_H

#include <string>
#include "IPlaylist.h"

class IPlaylistFactory {
public:
    virtual IPlaylist* create(const std::string& playlistName) = 0;

    virtual ~IPlaylistFactory() {}
};

#endif
