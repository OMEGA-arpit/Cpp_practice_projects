#include "PlayerService.h"

PlayerService::PlayerService(std::unique_ptr<IMusicLibrary> musicLibrary,
                             std::unique_ptr<IAudioPlayer> audioPlayer,
                             std::unique_ptr<IPersistenceManager> persistenceManager,
                             std::unique_ptr<IPlaylistFactory> playlistFactory)
    : musicLibrary(std::move(musicLibrary))
    , audioPlayer(std::move(audioPlayer))
    , persistenceManager(std::move(persistenceManager))
    , playlistFactory(std::move(playlistFactory))
    , activePlaylistName(Constants::EMPTY_STRING)
{
    this->audioPlayer->setOnSongEnd([this]() {
        this->next();
    });
}

const std::set<Song>& PlayerService::getAllSongs() const {
    return musicLibrary->getSongs();
}

const Song* PlayerService::searchSong(const std::string& songName) const {
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

bool PlayerService::isPlaying() const {
    return audioPlayer->isPlaying();
}

bool PlayerService::createPlaylist(const std::string& playlistName) {
    if (playlists.find(playlistName) != playlists.end()) 
    {
        return false;
    }

    playlists[playlistName] = playlistFactory->create(playlistName);
    return true;
}

bool PlayerService::deletePlaylist(const std::string& playlistName) {
    auto it = playlists.find(playlistName);

    if (it == playlists.end()) 
    {
        return false;
    }

    playlists.erase(it);

    if (activePlaylistName == playlistName) 
    {
        activePlaylistName = Constants::EMPTY_STRING;
    }

    return true;
}

bool PlayerService::selectPlaylist(const std::string& playlistName) {
    if (playlists.find(playlistName) == playlists.end()) 
    {
        return false;
    }

    activePlaylistName = playlistName;
    return true;
}

std::vector<std::string> PlayerService::getPlaylistNames() const {
    std::vector<std::string> playlistNames;
    playlistNames.reserve(playlists.size());

    for (const auto& [name, playlist] : playlists) 
    {
        playlistNames.push_back(name);
    }

    return playlistNames;
}

IPlaylist* PlayerService::getActivePlaylist() {
    if (activePlaylistName.empty()) 
    {
        return nullptr;
    }

    auto it = playlists.find(activePlaylistName);
    return (it != playlists.end()) ? it->second.get() : nullptr;
}

void PlayerService::loadPlaylists() {
    persistenceManager->loadPlaylists(playlists, playlistFactory.get());
}

void PlayerService::savePlaylists() {
    persistenceManager->savePlaylists(playlists);
}

