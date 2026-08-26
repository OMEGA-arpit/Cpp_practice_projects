#include "PlaylistControllerTest.h"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::DoAll;
using ::testing::SetArgReferee;
using ::testing::InSequence;

void GivenPlaylistControllerTest::SetUp() {
    playlistController = new PlaylistController(
        &mockPlayerService,
        &mockLogger,
        &mockInputHandler
    );
}

void GivenPlaylistControllerTest::TearDown() {
    delete playlistController;
}

// Handle Create Playlist

TEST_F(GivenPlaylistControllerTest, WhenCreatePlaylistCalledWithValidName_ThenServiceCreateCalled) {
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Chill Vibes"), Return()));
    EXPECT_CALL(mockPlayerService, createPlaylist("Chill Vibes")).WillOnce(Return(true));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_CREATED));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

TEST_F(GivenPlaylistControllerTest, WhenCreatePlaylistWithExistingName_ThenAlreadyExistsMessageShown) {
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Chill Vibes"), Return()));
    EXPECT_CALL(mockPlayerService, createPlaylist("Chill Vibes")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_ALREADY_EXISTS));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

// Delete Playlist

TEST_F(GivenPlaylistControllerTest, WhenDeleteExistingPlaylist_ThenDeletedMessageShown) {
    std::vector<std::string> playlistNames = {"Chill Vibes"};

    EXPECT_CALL(mockPlayerService, getPlaylistNames()).WillRepeatedly(Return(playlistNames));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLISTS_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Chill Vibes"));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Chill Vibes"), Return()));
    EXPECT_CALL(mockPlayerService, deletePlaylist("Chill Vibes")).WillOnce(Return(true));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DELETED));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

TEST_F(GivenPlaylistControllerTest, WhenDeleteNonExistentPlaylist_ThenNotFoundMessageShown) {
    std::vector<std::string> playlistNames = {"Chill Vibes"};

    EXPECT_CALL(mockPlayerService, getPlaylistNames()).WillRepeatedly(Return(playlistNames));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLISTS_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Chill Vibes"));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(mockPlayerService, deletePlaylist("NonExistent")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_NOT_FOUND));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

TEST_F(GivenPlaylistControllerTest, WhenDeleteCalledWithNoPlaylists_ThenNoDeleteAttempted) {
    std::vector<std::string> emptyNames;

    EXPECT_CALL(mockPlayerService, getPlaylistNames()).WillRepeatedly(Return(emptyNames));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_NO_PLAYLISTS));
    EXPECT_CALL(mockPlayerService, deletePlaylist(_)).Times(0);

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

// Open Playlist

TEST_F(GivenPlaylistControllerTest, WhenOpenExistingPlaylist_ThenPlaylistDetailEntered) {
    std::vector<std::string> playlistNames = {"Chill Vibes"};
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getPlaylistNames()).WillRepeatedly(Return(playlistNames));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLISTS_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Chill Vibes"));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Chill Vibes"), Return()));
    EXPECT_CALL(mockPlayerService, selectPlaylist("Chill Vibes")).WillOnce(Return(true));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(1))   
        .WillOnce(Return(8))   
        .WillOnce(Return(4));  
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(3);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(3);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY));

    playlistController->handlePlaylistMenu();
}

TEST_F(GivenPlaylistControllerTest, WhenOpenNonExistentPlaylist_ThenNotFoundMessageShown) {
    std::vector<std::string> playlistNames = {"Chill Vibes"};

    EXPECT_CALL(mockPlayerService, getPlaylistNames()).WillRepeatedly(Return(playlistNames));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLISTS_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Chill Vibes"));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(mockPlayerService, selectPlaylist("NonExistent")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_NOT_FOUND));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_PLAYLIST_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(1))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}

// Song Operations

TEST_F(GivenPlaylistControllerTest, WhenAddSongFoundInLibrary_ThenSongAddedSuccessfully) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    std::set<Song> librarySongs;
    Song song("Aahatein", "Songs/Aahatein.mp3");
    librarySongs.insert(song);

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlayerService, getAllSongs()).WillOnce(ReturnRef(librarySongs));
    EXPECT_CALL(mockPlaylist, searchSong(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlayerService, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(mockPlaylist, addSong(_)).WillOnce(Return(true));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_ADDED));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(4))   
        .WillOnce(Return(8));  
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Aahatein"));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenAddNonExistentSong_ThenSongNotFoundMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    std::set<Song> librarySongs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlayerService, getAllSongs()).WillOnce(ReturnRef(librarySongs));
    EXPECT_CALL(mockPlaylist, searchSong(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(mockPlayerService, searchSong("NonExistent")).WillOnce(Return(nullptr));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SEARCH_EMPTY));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(4))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_LIBRARY_EMPTY));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenAddSongAlreadyInPlaylist_ThenAlreadyExistsMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    std::set<Song> librarySongs;
    Song song("Aahatein", "Songs/Aahatein.mp3");
    librarySongs.insert(song);

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlayerService, getAllSongs()).WillOnce(ReturnRef(librarySongs));
    EXPECT_CALL(mockPlaylist, searchSong(_)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlayerService, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(mockPlaylist, addSong(_)).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_ALREADY_EXISTS));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(4))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(mockLogger, printMessage("1. Aahatein"));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenRemoveExistingSong_ThenSongRemovedMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlaylist, removeSong("Aahatein")).WillOnce(Return(true));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_REMOVED));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(5))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenRemoveNonExistentSong_ThenSongNotFoundMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(mockPlaylist, removeSong("NonExistent")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_NOT_FOUND));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(5))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenMoveSongUpwardSucceeds_ThenNoErrorMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlaylist, searchSong("Aahatein")).WillOnce(Return(nullptr));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_NOT_FOUND));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(6))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenMoveSongUpwardOnFirstSong_ThenAlreadyTopMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlaylist, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(mockPlaylist, moveSongUpward("Aahatein")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_CANNOT_MOVE));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_ALREADY_TOP));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(6))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenMoveSongDownwardOnNonExistentSong_ThenNotFoundMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(mockPlaylist, searchSong("NonExistent")).WillOnce(Return(nullptr));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_NOT_FOUND));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(7))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenMoveSongDownwardOnLastSong_ThenAlreadyBottomMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(mockPlaylist, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(mockPlaylist, moveSongDownward("Aahatein")).WillOnce(Return(false));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_CANNOT_MOVE));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONG_ALREADY_BOTTOM));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_ENTER_SONG_NAME));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(7))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenPlayCalledOnEmptyPlaylist_ThenEmptyMessageShown) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlaylist, getState()).WillOnce(Return(Constants::PlaybackState::STOPPED));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(3);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(1))
        .WillOnce(Return(8));

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenPauseCalledWhilePlaying_ThenPauseCalledOnService) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlaylist, getState()).WillOnce(Return(Constants::PlaybackState::PLAYING));
    EXPECT_CALL(mockPlayerService, pause());
    EXPECT_CALL(mockPlaylist, setState(Constants::PlaybackState::PAUSED));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PAUSED_SONG));

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(1))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenNextCalled_ThenServiceNextCalled) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlayerService, next());

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}

TEST_F(GivenPlaylistControllerTest, WhenPreviousCalled_ThenServicePreviousCalled) {
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;

    EXPECT_CALL(mockPlayerService, getActivePlaylist()).WillRepeatedly(Return(&mockPlaylist));
    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));
    EXPECT_CALL(mockPlaylist, getCurrentSong()).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(mockPlayerService, previous());

    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(8));
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_DETAIL_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_SONGS_HEADER)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_EMPTY)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);

    playlistController->handlePlaylistDetail();
}


TEST_F(GivenPlaylistControllerTest, WhenInvalidChoiceEntered_ThenInvalidChoiceMessageShown) {
    EXPECT_CALL(mockInputHandler, inputValue())
        .WillOnce(Return(99))
        .WillOnce(Return(4));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INVALID_CHOICE));
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_PLAYLIST_MENU)).Times(2);
    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(mockPlayerService, checkAndAdvance()).Times(2);

    playlistController->handlePlaylistMenu();
}
