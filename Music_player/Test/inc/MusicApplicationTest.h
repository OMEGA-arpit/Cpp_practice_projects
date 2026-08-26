#ifndef MUSIC_APPLICATION_TEST_H
#define MUSIC_APPLICATION_TEST_H

#include "MusicApplication.h"
#include "IMockPlayerService.h"
#include "IMockPlaylistController.h"
#include "IMockLogger.h"
#include "IMockInputHandler.h"
#include "Song.h"
#include "Constants.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <set>

class GivenMusicApplicationTest : public ::testing::Test {
protected:
    testing::NiceMock<IMockPlayerService>* mockPlayerService;
    testing::NiceMock<IMockPlaylistController>* mockPlaylistController;
    testing::NiceMock<IMockLogger>* mockLogger;
    testing::NiceMock<IMockInputHandler>* mockInputHandler;
    MusicApplication* musicApplication;

    void SetUp() override {
        mockPlayerService = new testing::NiceMock<IMockPlayerService>();
        mockPlaylistController = new testing::NiceMock<IMockPlaylistController>();
        mockLogger = new testing::NiceMock<IMockLogger>();
        mockInputHandler = new testing::NiceMock<IMockInputHandler>();

        musicApplication = new MusicApplication(
            mockPlayerService,
            mockPlaylistController,
            mockLogger,
            mockInputHandler
        );
    }

    void TearDown() override {
        delete musicApplication;
    }
};

#endif
