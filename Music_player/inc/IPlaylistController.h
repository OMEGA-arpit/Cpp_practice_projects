#ifndef IPLAYLIST_CONTROLLER_H
#define IPLAYLIST_CONTROLLER_H

/**
 * @brief Drives the playlist management UI.
 *
 * Handles the playlist main menu (open, create, delete) and the
 * per-playlist detail menu (play, next, previous, add/remove/move songs).
 */
class IPlaylistController {
public:
    /**
     * @brief Enters the playlist main menu loop.
     *
     * Blocks until the user selects "Back". All nested menus (detail view,
     * song operations) are invoked from within this call.
     */
    virtual void handlePlaylistMenu() = 0;

    virtual ~IPlaylistController() = default;
};

#endif
