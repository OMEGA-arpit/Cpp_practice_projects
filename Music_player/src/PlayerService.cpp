#include "PlayerService.h"

PlayerService::PlayerService(IMusicLibrary* musicLibrary,
                             IAudioPlayer* audioPlayer,
                             IPersistenceManager* persistenceManager,
                             IPlaylistFactory* playlistFactory)
    : musicLibrary(musicLibrary)
    , audioPlayer(audioPlayer)
    , persistenceManager(persistenceManager)
    , playlistFactory(playlistFactory)
    , activePlaylistName(Constants::EMPTY_STRING)
{
    audioPlayer->setOnSongEnd([this]() {
        this->next();
    });
}

const std::set<Song>& PlayerService::getAllSongs() {
    return musicLibrary->getSongs();
}

const Song* PlayerService::searchSong(const std::string& songName) {
    return musicLibrary->findSongByTitle(songName);
}


bool PlayerService::playSong(const Song& song) {
    audioPlayer->stop();
    audioPlayer->play(song.filePath);
    return audioPlayer->isPlaying();
}

void PlayerService::pause() {
    audioPlayer->pause();
}

void PlayerService::resume() {
    audioPlayer->resume();
}

void PlayerService::next() {
    IPlaylist* activePlaylist = getActivePlaylist();

    if (activePlaylist != nullptr) 
    {
        Song* nextSong = activePlaylist->nextSong();

        if (nextSong != nullptr) 
        {
            audioPlayer->stop();
            audioPlayer->play(nextSong->filePath);
        }
    }
}

void PlayerService::previous() {
    IPlaylist* activePlaylist = getActivePlaylist();

    if (activePlaylist != nullptr) 
    {
        Song* previousSong = activePlaylist->previousSong();

        if (previousSong != nullptr) 
        {
            audioPlayer->stop();
            audioPlayer->play(previousSong->filePath);
        }
    }
}

void PlayerService::checkAndAdvance() {
    audioPlayer->checkSongEnd();
}

bool PlayerService::isPlaying() {
    return audioPlayer->isPlaying();
}

bool PlayerService::createPlaylist(const std::string& playlistName) {
    bool playlistExists = (playlists.find(playlistName) != playlists.end());
    bool isPlaylistCreated = false;

    if (!playlistExists) 
    {
        playlists[playlistName] = playlistFactory->create(playlistName);
        isPlaylistCreated = true;
    }

    return isPlaylistCreated;
}

bool PlayerService::deletePlaylist(const std::string& playlistName) {
    std::map<std::string, IPlaylist*>::iterator playlistIterator = playlists.find(playlistName);
    bool playlistExists = (playlistIterator != playlists.end());

    if (playlistExists) 
    {
        delete playlistIterator->second;
        playlists.erase(playlistIterator);

        if (activePlaylistName == playlistName) 
        {
            activePlaylistName = Constants::EMPTY_STRING;
        }
    }

    return playlistExists;
}

bool PlayerService::selectPlaylist(const std::string& playlistName) {
    bool playlistExists = (playlists.find(playlistName) != playlists.end());

    if (playlistExists) 
    {
        activePlaylistName = playlistName;
    }

    return playlistExists;
}

std::vector<std::string> PlayerService::getPlaylistNames() {
    std::vector<std::string> playlistNames;
    std::map<std::string, IPlaylist*>::iterator playlistIterator = playlists.begin();

    while (playlistIterator != playlists.end()) 
    {
        playlistNames.push_back(playlistIterator->first);
        playlistIterator++;
    }

    return playlistNames;
}

IPlaylist* PlayerService::getActivePlaylist() {
    IPlaylist* activePlaylist = nullptr;

    if (!activePlaylistName.empty()) 
    {
        std::map<std::string, IPlaylist*>::iterator playlistIterator = playlists.find(activePlaylistName);

        if (playlistIterator != playlists.end()) 
        {
            activePlaylist = playlistIterator->second;
        }
    }

    return activePlaylist;
}


void PlayerService::loadPlaylists() {
    persistenceManager->loadPlaylists(playlists, playlistFactory);
}

void PlayerService::savePlaylists() {
    persistenceManager->savePlaylists(playlists);
}

PlayerService::~PlayerService() {
    std::map<std::string, IPlaylist*>::iterator playlistIterator = playlists.begin();

    while (playlistIterator != playlists.end()) 
    {
        delete playlistIterator->second;
        playlistIterator++;
    }

    delete musicLibrary;
    delete audioPlayer;
    delete persistenceManager;
    delete playlistFactory;
}
