#ifndef I_MOCK_AUDIO_PLAYER_H
#define I_MOCK_AUDIO_PLAYER_H

#include <gmock/gmock.h>
#include "IAudioPlayer.h"

class IMockAudioPlayer : public IAudioPlayer {
public:
    MOCK_METHOD(void, play, (const std::string& filePath), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, resume, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(bool, isPlaying, (), (override));
    MOCK_METHOD(void, setOnSongEnd, (std::function<void()> callback), (override));
    MOCK_METHOD(void, checkSongEnd, (), (override));
};

#endif
