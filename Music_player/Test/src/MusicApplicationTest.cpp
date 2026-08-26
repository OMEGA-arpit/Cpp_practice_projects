#include "MusicApplicationTest.h"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::DoAll;
using ::testing::SetArgReferee;

TEST_F(GivenMusicApplicationTest, WhenMainMenuStarts_ThenWelcomeMessageShown) {
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(5));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenMainMenuStarts_ThenPlaylistsLoaded) {
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, checkAndAdvance());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(5));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsOne_ThenPlaylistMenuCalled) {
    EXPECT_CALL(*mockPlaylistController, handlePlaylistMenu());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(1))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsTwoAndLibraryIsEmpty_ThenLibraryEmptyMessageShown) {
    std::set<Song> emptySongs;

    EXPECT_CALL(*mockPlayerService, getAllSongs()).WillOnce(ReturnRef(emptySongs));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_LIBRARY_EMPTY));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsTwoAndLibraryHasSongs_ThenSongNamesDisplayed) {
    std::set<Song> songs;
    songs.insert(Song("Aahatein", "Songs/Aahatein.mp3"));

    EXPECT_CALL(*mockPlayerService, getAllSongs()).WillOnce(ReturnRef(songs));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(*mockLogger, printMessage("1. Aahatein"));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsThreeAndSongNotFound_ThenSearchEmptyMessageShown) {
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_SEARCH_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("NonExistent"), Return()));
    EXPECT_CALL(*mockPlayerService, searchSong("NonExistent")).WillOnce(Return(nullptr));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_SEARCH_EMPTY));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsThreeAndSongFoundAndUserPressesBack_ThenPlaySongNotCalled) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_SEARCH_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(*mockPlayerService, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_FOUND + song.name));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PLAY_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputCharacter()).WillOnce(Return('b'));
    EXPECT_CALL(*mockPlayerService, playSong(_)).Times(0);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsThreeAndSongFoundAndUserPressesPlay_ThenPlaySongCalled) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_SEARCH_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(*mockPlayerService, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_FOUND + song.name));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PLAY_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputCharacter()).WillOnce(Return('p'));
    EXPECT_CALL(*mockPlayerService, playSong(song));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_NOW_PLAYING + song.name));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsThreeAndSongFoundAndInvalidKeyPressed_ThenInvalidChoiceShown) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_SEARCH_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputString(_))
        .WillOnce(DoAll(SetArgReferee<0>("Aahatein"), Return()));
    EXPECT_CALL(*mockPlayerService, searchSong("Aahatein")).WillOnce(Return(&song));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_FOUND + song.name));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PLAY_PROMPT));
    EXPECT_CALL(*mockInputHandler, inputCharacter()).WillOnce(Return('x'));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INVALID_CHOICE));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(3))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsFourAndSongIsPlaying_ThenPauseCalled) {
    EXPECT_CALL(*mockPlayerService, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*mockPlayerService, pause());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PAUSED_SONG));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(4))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsFourAndSongIsPaused_ThenResumeCalled) {
    EXPECT_CALL(*mockPlayerService, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*mockPlayerService, resume());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PLAYING_SONG));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(4))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenChoiceIsFive_ThenPlaylistssavePlaylistsdAndExitMessageShown) {
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance());
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE));
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenInvalidChoiceEntered_ThenInvalidChoiceMessageShown) {
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INVALID_CHOICE));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockPlayerService, savePlaylists());
    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(99))
        .WillOnce(Return(5));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    musicApplication->handleMainMenu();
}

TEST_F(GivenMusicApplicationTest, WhenMenuLoopsTwiceBeforeExit_ThenCheckAndAdvanceCalledTwice) {
    std::set<Song> emptySongs;

    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_WELCOME));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_MAIN_MENU)).Times(2);  
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_INPUT_CHOICE)).Times(2);
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_LIBRARY_HEADER));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_LIBRARY_EMPTY));
    EXPECT_CALL(*mockLogger, printMessage(Constants::MSG_PROGRAM_EXIT));

    EXPECT_CALL(*mockPlayerService, loadPlaylists());
    EXPECT_CALL(*mockPlayerService, checkAndAdvance()).Times(2);
    EXPECT_CALL(*mockPlayerService, getAllSongs()).WillOnce(ReturnRef(emptySongs));
    EXPECT_CALL(*mockPlayerService, savePlaylists());

    EXPECT_CALL(*mockInputHandler, inputValue())
        .WillOnce(Return(2))
        .WillOnce(Return(5));

    musicApplication->handleMainMenu();
}
