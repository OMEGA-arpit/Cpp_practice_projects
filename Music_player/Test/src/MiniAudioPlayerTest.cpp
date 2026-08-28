#include "MiniAudioPlayerTest.h"

using ::testing::_;

TEST_F(GivenMiniAudioPlayerTest, WhenJustConstructed_ThenIsPlayingReturnsFalse) {
    EXPECT_FALSE(audioPlayer->isPlaying());
}

TEST_F(GivenMiniAudioPlayerTest, WhenPauseCalledWithNoSoundLoaded_ThenIsPlayingRemainsFlase) {
    audioPlayer->pause();
    EXPECT_FALSE(audioPlayer->isPlaying());
}

TEST_F(GivenMiniAudioPlayerTest, WhenResumeCalledWithNoSoundLoaded_ThenIsPlayingRemainsFalse) {
    audioPlayer->resume();
    EXPECT_FALSE(audioPlayer->isPlaying());
}

TEST_F(GivenMiniAudioPlayerTest, WhenStopCalledWithNoSoundLoaded_ThenIsPlayingRemainsFalse) {
    audioPlayer->stop();
    EXPECT_FALSE(audioPlayer->isPlaying());
}

TEST_F(GivenMiniAudioPlayerTest, WhenSongEndCallbackSet_ThenCallbackIsNotFiredImmediately) {
    bool callbackFired = false;

    audioPlayer->setOnSongEnd([&callbackFired]() {
        callbackFired = true;
    });

    EXPECT_FALSE(callbackFired);
}

TEST_F(GivenMiniAudioPlayerTest, WhenCheckSongEndCalledWhileNotPlaying_ThenCallbackNotFired) {
    bool callbackFired = false;

    audioPlayer->setOnSongEnd([&callbackFired]() {
        callbackFired = true;
    });

    audioPlayer->checkSongEnd();
    EXPECT_FALSE(callbackFired);
}

TEST_F(GivenMiniAudioPlayerTest, WhenInvalidFilePathPlayed_ThenIsPlayingReturnsFalse) {
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_AUDIO_LOAD_FAILED + "invalid.mp3"));
    audioPlayer->play("invalid.mp3");
    EXPECT_FALSE(audioPlayer->isPlaying());
}

TEST_F(GivenMiniAudioPlayerTest, WhenInvalidFilePathPlayed_ThenLoggerPrintsError) {
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_AUDIO_LOAD_FAILED + "invalid.mp3"));
    audioPlayer->play("invalid.mp3");
}
