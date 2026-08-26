#include "MusicApplicationFactory.h"
#include "MusicLibrary.h"
#include "MiniAudioPlayer.h"
#include "PersistenceManager.h"
#include "PlaylistFactory.h"
#include "PlayerService.h"
#include "Logger.h"
#include "InputHandler.h"
#include "PlaylistController.h"

MusicApplication* MusicApplicationFactory::create() {
    ILogger* logger = new Logger();
    IInputHandler* inputHandler = new InputHandler(logger);

    IMusicLibrary* musicLibrary = new MusicLibrary();
    IAudioPlayer* audioPlayer = new MiniAudioPlayer(logger);
    IPersistenceManager* manager = new PersistenceManager(logger);
    IPlaylistFactory* playlistFactory = new PlaylistFactory();

    IPlayerService* service = new PlayerService(musicLibrary, audioPlayer,
        manager, playlistFactory);

    IPlaylistController* controller = new PlaylistController(service, logger, inputHandler);

    return new MusicApplication(service, controller, logger, inputHandler);
}
