#ifndef MINI_AUDIO_PLAYER_H
#define MINI_AUDIO_PLAYER_H

#include "IAudioPlayer.h"
#include "ILogger.h"
#include <functional>
#include <string>

class MiniAudioPlayer : public IAudioPlayer {
    ILogger* logger;
    struct AudioResources;
    AudioResources* audioResources;
    bool isCurrentlyPlaying;
    std::function<void()> onSongEndCallback;

public:
    MiniAudioPlayer(ILogger* logger);
    ~MiniAudioPlayer() override;

    MiniAudioPlayer(const MiniAudioPlayer&) = delete;
    MiniAudioPlayer& operator=(const MiniAudioPlayer&) = delete;

    void play(const std::string& filePath) override;
    void pause() override;
    void resume() override;
    void stop() override;
    bool isPlaying() override;

    void setOnSongEnd(std::function<void()> callback) override;
    void checkSongEnd() override;
};

#endif
