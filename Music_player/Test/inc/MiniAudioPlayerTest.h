#ifndef MINI_AUDIO_PLAYER_TEST_H
#define MINI_AUDIO_PLAYER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MiniAudioPlayer.h"
#include "IMockLogger.h"

class GivenMiniAudioPlayerTest : public ::testing::Test {
protected:
    IMockLogger mockLogger;
    MiniAudioPlayer* audioPlayer;

    void SetUp() override {
        audioPlayer = new MiniAudioPlayer(&mockLogger);
    }

    void TearDown() override {
        delete audioPlayer;
    }
};

#endif
