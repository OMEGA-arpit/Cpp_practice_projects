#ifndef IPLAYLIST_CONTROLLER_H
#define IPLAYLIST_CONTROLLER_H

class IPlaylistController {
public:
    virtual void handlePlaylistMenu() = 0;

    virtual ~IPlaylistController() {};
};

#endif
