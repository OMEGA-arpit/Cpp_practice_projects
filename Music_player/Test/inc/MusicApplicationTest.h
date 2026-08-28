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
#include <memory>
#include <set>

class GivenMusicApplicationTest : public ::testing::Test {
protected:
    // Observer (non-owning) pointers — valid for the lifetime of musicApplication
    testing::NiceMock<IMockPlayerService>* mockPlayerService;
    testing::NiceMock<IMockPlaylistController>* mockPlaylistController;
    testing::NiceMock<IMockLogger>* mockLogger;
    testing::NiceMock<IMockInputHandler>* mockInputHandler;
    MusicApplication* musicApplication;

    void SetUp() override {
        auto svcPtr  = std::make_unique<testing::NiceMock<IMockPlayerService>>();
        auto ctrlPtr = std::make_unique<testing::NiceMock<IMockPlaylistController>>();
        auto logPtr  = std::make_unique<testing::NiceMock<IMockLogger>>();
        auto inpPtr  = std::make_unique<testing::NiceMock<IMockInputHandler>>();

        mockPlayerService      = svcPtr.get();
        mockPlaylistController = ctrlPtr.get();
        mockLogger             = logPtr.get();
        mockInputHandler       = inpPtr.get();

        musicApplication = new MusicApplication(
            std::move(svcPtr), std::move(ctrlPtr),
            std::move(logPtr), std::move(inpPtr));
    }

    void TearDown() override {
        delete musicApplication;  // also deletes all owned mocks via unique_ptr
    }
};

#endif
