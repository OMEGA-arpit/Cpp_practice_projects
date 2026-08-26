#include "PersistenceManagerTest.h"
#include <filesystem>

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;

void GivenPersistenceManagerTest::SetUp() {
    testFilePath = "testPlaylists.txt";
    persistenceManager = new PersistenceManager(&mockLogger, testFilePath);

    ON_CALL(mockLogger, printMessage(testing::_))
        .WillByDefault(testing::Return());
}

void GivenPersistenceManagerTest::TearDown() {
    std::filesystem::remove(testFilePath);
    delete persistenceManager;
}

// Save Playlists

TEST_F(GivenPersistenceManagerTest, WhenPlaylistsSaved_ThenFileIsCreated) {
    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylist mockPlaylist;
    std::list<Song> emptySongs;

    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(emptySongs));

    playlists["Chill Vibes"] = &mockPlaylist;
    persistenceManager->savePlaylists(playlists);

    EXPECT_TRUE(std::filesystem::exists(testFilePath));
}

TEST_F(GivenPersistenceManagerTest, WhenPlaylistWithSongsSaved_ThenFileContainsPlaylistName) {
    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    songs.push_back(Song("Aahatein", "Songs/Aahatein.mp3"));

    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));

    playlists["Chill Vibes"] = &mockPlaylist;
    persistenceManager->savePlaylists(playlists);

    std::ifstream file(testFilePath);
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    EXPECT_NE(content.find("Chill Vibes"), std::string::npos);
}

TEST_F(GivenPersistenceManagerTest, WhenPlaylistWithSongsSaved_ThenFileContainsSongName) {
    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylist mockPlaylist;
    std::list<Song> songs;
    songs.push_back(Song("Aahatein", "Songs/Aahatein.mp3"));

    EXPECT_CALL(mockPlaylist, getSongs()).WillRepeatedly(ReturnRef(songs));

    playlists["Chill Vibes"] = &mockPlaylist;
    persistenceManager->savePlaylists(playlists);

    std::ifstream file(testFilePath);
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    EXPECT_NE(content.find("Aahatein"), std::string::npos);
}

TEST_F(GivenPersistenceManagerTest, WhenEmptyPlaylistsSaved_ThenFileIsCreated) {
    std::map<std::string, IPlaylist*> playlists;
    persistenceManager->savePlaylists(playlists);
    EXPECT_TRUE(std::filesystem::exists(testFilePath));
}

// Load Playlist

TEST_F(GivenPersistenceManagerTest, WhenFileDoesNotExist_ThenLoggerPrintsError) {
    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylistFactory mockFactory;
    PersistenceManager managerWithBadPath(&mockLogger, "nonexistent.txt");

    EXPECT_CALL(mockLogger, printMessage(Constants::MSG_FILE_LOAD_FAILED + "nonexistent.txt"));

    managerWithBadPath.loadPlaylists(playlists, &mockFactory);
}

TEST_F(GivenPersistenceManagerTest, WhenValidFileLoaded_ThenPlaylistIsCreated) {
    std::ofstream file(testFilePath);
    file << "PLAYLIST:Chill Vibes\n";
    file << "Aahatein|Songs/Aahatein.mp3\n";
    file.close();

    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylistFactory mockFactory;
    IMockPlaylist* mockPlaylist = new IMockPlaylist();

    EXPECT_CALL(mockFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, addSong(testing::_)).WillOnce(Return(true));

    persistenceManager->loadPlaylists(playlists, &mockFactory);

    EXPECT_EQ(playlists.size(), 1);
    EXPECT_NE(playlists.find("Chill Vibes"), playlists.end());

    delete mockPlaylist;
}

TEST_F(GivenPersistenceManagerTest, WhenFileHasMultiplePlaylists_ThenAllPlaylistsCreated) {
    std::ofstream file(testFilePath);
    file << "PLAYLIST:Chill Vibes\n";
    file << "Aahatein|Songs/Aahatein.mp3\n";
    file << "PLAYLIST:Road Trip\n";
    file << "Believer|Songs/Believer.mp3\n";
    file.close();

    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylistFactory mockFactory;
    IMockPlaylist* mockPlaylistOne = new IMockPlaylist();
    IMockPlaylist* mockPlaylistTwo = new IMockPlaylist();

    EXPECT_CALL(mockFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylistOne));
    EXPECT_CALL(mockFactory, create("Road Trip")).WillOnce(Return(mockPlaylistTwo));
    EXPECT_CALL(*mockPlaylistOne, addSong(testing::_)).WillOnce(Return(true));
    EXPECT_CALL(*mockPlaylistTwo, addSong(testing::_)).WillOnce(Return(true));

    persistenceManager->loadPlaylists(playlists, &mockFactory);

    EXPECT_EQ(playlists.size(), 2);

    delete mockPlaylistOne;
    delete mockPlaylistTwo;
}

TEST_F(GivenPersistenceManagerTest, WhenFileIsEmpty_ThenNoPlaylistsCreated) {
    std::ofstream file(testFilePath);
    file.close();

    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylistFactory mockFactory;

    persistenceManager->loadPlaylists(playlists, &mockFactory);

    EXPECT_TRUE(playlists.empty());
}

TEST_F(GivenPersistenceManagerTest, WhenLineHasNoSeparator_ThenSongIsNotAdded) {
    std::ofstream file(testFilePath);
    file << "PLAYLIST:Chill Vibes\n";
    file << "InvalidLineWithNoSeparator\n";
    file.close();

    std::map<std::string, IPlaylist*> playlists;
    IMockPlaylistFactory mockFactory;
    IMockPlaylist* mockPlaylist = new IMockPlaylist();

    EXPECT_CALL(mockFactory, create("Chill Vibes")).WillOnce(Return(mockPlaylist));
    EXPECT_CALL(*mockPlaylist, addSong(testing::_)).Times(0);

    persistenceManager->loadPlaylists(playlists, &mockFactory);

    delete mockPlaylist;
}
