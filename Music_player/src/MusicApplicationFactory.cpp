#include "MusicApplicationFactory.h"
#include "MusicLibrary.h"
#include "MiniAudioPlayer.h"
#include "PersistenceManager.h"
#include "PlaylistFactory.h"
#include "PlayerService.h"
#include "Logger.h"
#include "InputHandler.h"
#include "PlaylistController.h"
#include <memory>

std::unique_ptr<MusicApplication> MusicApplicationFactory::create() {
    auto logger = std::make_unique<Logger>();
    auto inputHandler = std::make_unique<InputHandler>(logger.get());

    auto musicLibrary = std::make_unique<MusicLibrary>();
    auto audioPlayer = std::make_unique<MiniAudioPlayer>(logger.get());
    auto manager = std::make_unique<PersistenceManager>(logger.get());
    auto playlistFactory = std::make_unique<PlaylistFactory>();

    auto service = std::make_unique<PlayerService>(
        std::move(musicLibrary), std::move(audioPlayer),
        std::move(manager), std::move(playlistFactory));

    auto controller = std::make_unique<PlaylistController>(
        service.get(), logger.get(), inputHandler.get());

    return std::make_unique<MusicApplication>(
        std::move(service), std::move(controller),
        std::move(logger), std::move(inputHandler));
}
