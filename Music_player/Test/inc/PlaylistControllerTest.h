#ifndef PLAYLIST_CONTROLLER_TEST_H
#define PLAYLIST_CONTROLLER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PlaylistController.h"
#include "IMockPlayerService.h"
#include "IMockLogger.h"
#include "IMockInputHandler.h"
#include "IMockPlaylist.h"

class GivenPlaylistControllerTest : public ::testing::Test {
protected:
    testing::NiceMock<IMockPlayerService> mockPlayerService;
    testing::NiceMock<IMockLogger> mockLogger;
    testing::NiceMock<IMockInputHandler> mockInputHandler;
    PlaylistController* playlistController;

    void SetUp() override;
    void TearDown() override;
};

#endif
