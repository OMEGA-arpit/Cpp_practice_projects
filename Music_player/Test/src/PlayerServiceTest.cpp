#include "PlayerServiceTest.h"

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

void GivenPlayerServiceTest::SetUp() {
    mockMusicLibrary = new testing::NiceMock<IMockMusicLibrary>();
    mockAudioPlayer = new testing::NiceMock<IMockAudioPlayer>();
    mockPersistenceManager = new testing::NiceMock<IMockPersistenceManager>();
    mockPlaylistFactory = new testing::NiceMock<IMockPlaylistFactory>();

    playerService = new PlayerService(
        mockMusicLibrary,
        mockAudioPlayer,
        mockPersistenceManager,
        mockPlaylistFactory
    );
}

void GivenPlayerServiceTest::TearDown() {
    delete playerService;
}

TEST_F(GivenPlayerServiceTest, WhenGetAllSongsCalled_ThenDelegatesToMusicLibrary) {
    std::set<Song> songs;
    songs.insert(Song("Aahatein", "Songs/Aahatein.mp3"));

    EXPECT_CALL(*mockMusicLibrary, getSongs()).WillOnce(ReturnRef(songs));

    EXPECT_EQ(playerService->getAllSongs().size(), 1);
}


TEST_F(GivenPlayerServiceTest, WhenSearchingSong_ThenDelegatesToMusicLibrary) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockMusicLibrary, findSongByTitle("Aahatein")).WillOnce(Return(&song));

    const Song* result = playerService->searchSong("Aahatein");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->name, "Aahatein");
}

TEST_F(GivenPlayerServiceTest, WhenSearchingNonExistentSong_ThenReturnsNull) {
    EXPECT_CALL(*mockMusicLibrary, findSongByTitle("NonExistent")).WillOnce(Return(nullptr));

    EXPECT_EQ(playerService->searchSong("NonExistent"), nullptr);
}


TEST_F(GivenPlayerServiceTest, WhenPlaySongCalled_ThenAudioPlayerStopsThenPlays) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    testing::InSequence sequence;
    EXPECT_CALL(*mockAudioPlayer, stop());
    EXPECT_CALL(*mockAudioPlayer, play("Songs/Aahatein.mp3"));
    EXPECT_CALL(*mockAudioPlayer, isPlaying()).WillOnce(Return(true));

    playerService->playSong(song);
}

TEST_F(GivenPlayerServiceTest, WhenPlaySongFails_ThenReturnsFalse) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockAudioPlayer, stop());
    EXPECT_CALL(*mockAudioPlayer, play("Songs/Aahatein.mp3"));
    EXPECT_CALL(*mockAudioPlayer, isPlaying()).WillOnce(Return(false));

    bool result = playerService->playSong(song);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlayerServiceTest, WhenPlaySongSucceeds_ThenReturnsTrue) {
    Song song("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockAudioPlayer, stop());
    EXPECT_CALL(*mockAudioPlayer, play("Songs/Aahatein.mp3"));
    EXPECT_CALL(*mockAudioPlayer, isPlaying()).WillOnce(Return(true));

    EXPECT_TRUE(playerService->playSong(song));
}


TEST_F(GivenPlayerServiceTest, WhenPauseCalled_ThenDelegatesToAudioPlayer) {
    EXPECT_CALL(*mockAudioPlayer, pause());
    playerService->pause();
}


TEST_F(GivenPlayerServiceTest, WhenResumeCalled_ThenDelegatesToAudioPlayer) {
    EXPECT_CALL(*mockAudioPlayer, resume());
    playerService->resume();
}


TEST_F(GivenPlayerServiceTest, WhenCheckAndAdvanceCalled_ThenDelegatesToAudioPlayer) {
    EXPECT_CALL(*mockAudioPlayer, checkSongEnd());
    playerService->checkAndAdvance();
}


TEST_F(GivenPlayerServiceTest, WhenIsPlayingCalled_ThenDelegatesToAudioPlayer) {
    EXPECT_CALL(*mockAudioPlayer, isPlaying()).WillOnce(Return(true));
    EXPECT_TRUE(playerService->isPlaying());
}

TEST_F(GivenPlayerServiceTest, WhenAudioPlayerNotPlaying_ThenIsPlayingReturnsFalse) {
    EXPECT_CALL(*mockAudioPlayer, isPlaying()).WillOnce(Return(false));
    EXPECT_FALSE(playerService->isPlaying());
}


TEST_F(GivenPlayerServiceTest, WhenPlaylistCreated_ThenReturnsTrue) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    EXPECT_TRUE(playerService->createPlaylist("Chill Vibes"));
}

TEST_F(GivenPlayerServiceTest, WhenSamePlaylistCreatedTwice_ThenSecondReturnsFalse) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    playerService->createPlaylist("Chill Vibes");
    EXPECT_FALSE(playerService->createPlaylist("Chill Vibes"));
}

TEST_F(GivenPlayerServiceTest, WhenPlaylistDeletedAndRecreated_ThenReturnsTrue) {
    IMockPlaylist* mockPlaylistOne = new IMockPlaylist();
    IMockPlaylist* mockPlaylistTwo = new IMockPlaylist();

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes"))
        .WillOnce(Return(mockPlaylistOne))
        .WillOnce(Return(mockPlaylistTwo));

    playerService->createPlaylist("Chill Vibes");
    playerService->deletePlaylist("Chill Vibes");
    EXPECT_TRUE(playerService->createPlaylist("Chill Vibes"));
}


TEST_F(GivenPlayerServiceTest, WhenExistingPlaylistDeleted_ThenReturnsTrue) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    playerService->createPlaylist("Chill Vibes");
    EXPECT_TRUE(playerService->deletePlaylist("Chill Vibes"));
}

TEST_F(GivenPlayerServiceTest, WhenNonExistentPlaylistDeleted_ThenReturnsFalse) {
    EXPECT_FALSE(playerService->deletePlaylist("NonExistent"));
}

TEST_F(GivenPlayerServiceTest, WhenActivePlaylistDeleted_ThenActivePlaylistBecomesNull) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");
    playerService->deletePlaylist("Chill Vibes");

    EXPECT_EQ(playerService->getActivePlaylist(), nullptr);
}


TEST_F(GivenPlayerServiceTest, WhenExistingPlaylistSelected_ThenReturnsTrue) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    playerService->createPlaylist("Chill Vibes");
    EXPECT_TRUE(playerService->selectPlaylist("Chill Vibes"));
}

TEST_F(GivenPlayerServiceTest, WhenNonExistentPlaylistSelected_ThenReturnsFalse) {
    EXPECT_FALSE(playerService->selectPlaylist("NonExistent"));
}


TEST_F(GivenPlayerServiceTest, WhenNoPlaylistSelected_ThenActivePlaylistIsNull) {
    EXPECT_EQ(playerService->getActivePlaylist(), nullptr);
}

TEST_F(GivenPlayerServiceTest, WhenPlaylistSelected_ThenGetActivePlaylistReturnsIt) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");

    EXPECT_EQ(playerService->getActivePlaylist(), mockPlaylist);
}


TEST_F(GivenPlayerServiceTest, WhenNoPlaylistsExist_ThenGetPlaylistNamesReturnsEmpty) {
    EXPECT_TRUE(playerService->getPlaylistNames().empty());
}

TEST_F(GivenPlayerServiceTest, WhenTwoPlaylistsCreated_ThenGetPlaylistNamesReturnsBoth) {
    IMockPlaylist* mockPlaylistOne = new IMockPlaylist();
    IMockPlaylist* mockPlaylistTwo = new IMockPlaylist();

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylistOne));
    EXPECT_CALL(*mockPlaylistFactory, create("Road Trip")).WillOnce(Return(mockPlaylistTwo));

    playerService->createPlaylist("Chill Vibes");
    playerService->createPlaylist("Road Trip");

    EXPECT_EQ(playerService->getPlaylistNames().size(), 2);
}

TEST_F(GivenPlayerServiceTest, WhenTwoPlaylistsCreated_ThenGetPlaylistNamesContainsCorrectNames) {
    IMockPlaylist* mockPlaylistOne = new IMockPlaylist();
    IMockPlaylist* mockPlaylistTwo = new IMockPlaylist();

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylistOne));
    EXPECT_CALL(*mockPlaylistFactory, create("Road Trip")).WillOnce(Return(mockPlaylistTwo));

    playerService->createPlaylist("Chill Vibes");
    playerService->createPlaylist("Road Trip");

    std::vector<std::string> names = playerService->getPlaylistNames();
    bool chillVibesFound = (std::find(names.begin(), names.end(), "Chill Vibes") != names.end());
    bool roadTripFound = (std::find(names.begin(), names.end(), "Road Trip") != names.end());

    EXPECT_TRUE(chillVibesFound);
    EXPECT_TRUE(roadTripFound);
}


TEST_F(GivenPlayerServiceTest, WhenNextCalledWithNoActivePlaylist_ThenAudioPlayerNotCalled) {
    EXPECT_CALL(*mockAudioPlayer, play(_)).Times(0);
    playerService->next();
}

TEST_F(GivenPlayerServiceTest, WhenNextCalledWithActivePlaylist_ThenPlaysNextSong) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    Song nextSong("Believer", "Songs/Believer.mp3");

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, nextSong()).WillOnce(Return(&nextSong));
    EXPECT_CALL(*mockAudioPlayer, stop());
    EXPECT_CALL(*mockAudioPlayer, play("Songs/Believer.mp3"));

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");
    playerService->next();
}

TEST_F(GivenPlayerServiceTest, WhenNextSongReturnsNull_ThenAudioPlayerNotCalled) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, nextSong()).WillOnce(Return(nullptr));
    EXPECT_CALL(*mockAudioPlayer, play(_)).Times(0);

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");
    playerService->next();
}


TEST_F(GivenPlayerServiceTest, WhenPreviousCalledWithNoActivePlaylist_ThenAudioPlayerNotCalled) {
    EXPECT_CALL(*mockAudioPlayer, play(_)).Times(0);
    playerService->previous();
}

TEST_F(GivenPlayerServiceTest, WhenPreviousCalledWithActivePlaylist_ThenPlaysPreviousSong) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();
    Song previousSong("Aahatein", "Songs/Aahatein.mp3");

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, previousSong()).WillOnce(Return(&previousSong));
    EXPECT_CALL(*mockAudioPlayer, stop());
    EXPECT_CALL(*mockAudioPlayer, play("Songs/Aahatein.mp3"));

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");
    playerService->previous();
}

TEST_F(GivenPlayerServiceTest, WhenPreviousSongReturnsNull_ThenAudioPlayerNotCalled) {
    IMockPlaylist* mockPlaylist = new IMockPlaylist();

    EXPECT_CALL(*mockPlaylistFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, previousSong()).WillOnce(Return(nullptr));
    EXPECT_CALL(*mockAudioPlayer, play(_)).Times(0);

    playerService->createPlaylist("Chill Vibes");
    playerService->selectPlaylist("Chill Vibes");
    playerService->previous();
}


TEST_F(GivenPlayerServiceTest, WhenSaveCalled_ThenDelegatesToPersistenceManager) {
    EXPECT_CALL(*mockPersistenceManager, savePlaylists(_));
    playerService->savePlaylists();
}

TEST_F(GivenPlayerServiceTest, WhenLoadCalled_ThenDelegatesToPersistenceManager) {
    EXPECT_CALL(*mockPersistenceManager, loadPlaylists(_, mockPlaylistFactory));
    playerService->loadPlaylists();
}
