#ifndef IAUDIO_PLAYER_H
#define IAUDIO_PLAYER_H

#include <string>
#include <functional>

class IAudioPlayer {
public:
    virtual void play(const std::string& filePath) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() = 0;

    virtual void setOnSongEnd(std::function<void()> callback) = 0;
    virtual void checkSongEnd() = 0;

    virtual ~IAudioPlayer() {}
};

#endif
