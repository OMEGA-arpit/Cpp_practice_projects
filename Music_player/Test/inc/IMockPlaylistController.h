#ifndef I_MOCK_PLAYLIST_CONTROLLER_H
#define I_MOCK_PLAYLIST_CONTROLLER_H

#include <gmock/gmock.h>
#include "IPlaylistController.h"

class IMockPlaylistController : public IPlaylistController {
public:
    MOCK_METHOD(void, handlePlaylistMenu, (), (override));
};

#endif
