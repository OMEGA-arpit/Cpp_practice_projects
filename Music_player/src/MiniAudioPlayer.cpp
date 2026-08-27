#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "MiniAudioPlayer.h"
#include "Constants.h"

struct MiniAudioPlayer::AudioResources {
    ma_engine engine;
    ma_sound sound;
    bool engineReady;
    bool soundReady;

    AudioResources() : engineReady(false), soundReady(false) {}
};

MiniAudioPlayer::MiniAudioPlayer(ILogger* logger)
    : logger(logger)
    , audioResources(new AudioResources())
    , isCurrentlyPlaying(false)
{
    if (ma_engine_init(nullptr, &audioResources->engine) != MA_SUCCESS)
    {
        logger->printMessage(Constants::MSG_AUDIO_ENGINE_FAILED);
        audioResources->engineReady = false;
    }
    else
    {
        audioResources->engineReady = true;
    }
}

void MiniAudioPlayer::play(const std::string& filePath) {
    // Uninitialise any previously loaded sound before loading the new one.
    // miniaudio requires explicit cleanup; failing to do so leaks engine resources.
    if (audioResources->soundReady)
    {
        ma_sound_stop(&audioResources->sound);
        ma_sound_uninit(&audioResources->sound);
        audioResources->soundReady = false;
    }

    // MA_SOUND_FLAG_ASYNC loads the audio data on a background thread so the
    // main thread is not blocked while reading a large file. Playback starts
    // immediately after the header is decoded, giving low perceived latency.
    ma_result loadResult = ma_sound_init_from_file(
        &audioResources->engine,
        filePath.c_str(),
        MA_SOUND_FLAG_ASYNC,
        nullptr,
        nullptr,
        &audioResources->sound
    );

    if (loadResult != MA_SUCCESS)
    {
        logger->printMessage(Constants::MSG_AUDIO_LOAD_FAILED + filePath);
        isCurrentlyPlaying = false;
    }
    else
    {
        audioResources->soundReady = true;

        if (ma_sound_start(&audioResources->sound) != MA_SUCCESS)
        {
            logger->printMessage(Constants::MSG_AUDIO_START_FAILED + filePath);
            isCurrentlyPlaying = false;
        }
        else
        {
            isCurrentlyPlaying = true;
        }
    }
}

void MiniAudioPlayer::pause() {
    if (audioResources->soundReady && isCurrentlyPlaying)
    {
        ma_sound_stop(&audioResources->sound);
        isCurrentlyPlaying = false;
    }
}

void MiniAudioPlayer::resume() {
    if (audioResources->soundReady && !isCurrentlyPlaying)
    {
        ma_sound_start(&audioResources->sound);
        isCurrentlyPlaying = true;
    }
}

void MiniAudioPlayer::stop() {
    if (audioResources->soundReady)
    {
        ma_sound_stop(&audioResources->sound);
        ma_sound_seek_to_pcm_frame(&audioResources->sound, 0);
        isCurrentlyPlaying = false;
    }
}

bool MiniAudioPlayer::isPlaying() {
    return isCurrentlyPlaying;
}

void MiniAudioPlayer::setOnSongEnd(std::function<void()> songEndCallback) {
    onSongEndCallback = songEndCallback;
}

void MiniAudioPlayer::checkSongEnd() {
    // ma_sound_is_playing returns false once the sound has decoded its last
    // frame and stopped. We compare against our own isCurrentlyPlaying flag
    // so the callback fires exactly once per natural track end and is not
    // triggered after an explicit stop() or pause() call.
    if (audioResources->soundReady && isCurrentlyPlaying)
    {
        if (!ma_sound_is_playing(&audioResources->sound))
        {
            isCurrentlyPlaying = false;

            if (onSongEndCallback)
            {
                onSongEndCallback();
            }
        }
    }
}

MiniAudioPlayer::~MiniAudioPlayer() {
    if (audioResources != nullptr)
    {
        if (audioResources->soundReady)
        {
            ma_sound_uninit(&audioResources->sound);
        }
        if (audioResources->engineReady)
        {
            ma_engine_uninit(&audioResources->engine);
        }
        delete audioResources;
    }
}
