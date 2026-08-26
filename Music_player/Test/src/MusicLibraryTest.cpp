#include "MusicLibraryTest.h"
#include <filesystem>
#include <fstream>

void GivenMusicLibraryTest::SetUp() {
    std::filesystem::create_directory("TestSongs");
    std::ofstream("TestSongs/Aahatein.mp3").close();
    std::ofstream("TestSongs/Believer.mp3").close();
    std::ofstream("TestSongs/Tum Hi Ho.mp3").close();
    musicLibrary = new MusicLibrary("TestSongs");
}

void GivenMusicLibraryTest::TearDown() {
    std::filesystem::remove_all("TestSongs");
    delete musicLibrary;
}

void GivenEmptyMusicLibraryTest::SetUp() {
    std::filesystem::create_directory("TestSongsEmpty");
    musicLibrary = new MusicLibrary("TestSongsEmpty");
}

void GivenEmptyMusicLibraryTest::TearDown() {
    std::filesystem::remove_all("TestSongsEmpty");
    delete musicLibrary;
}

void GivenInvalidFolderMusicLibraryTest::SetUp() {
    musicLibrary = new MusicLibrary("NonExistentFolder");
}

void GivenInvalidFolderMusicLibraryTest::TearDown() {
    delete musicLibrary;
}

TEST_F(GivenMusicLibraryTest, WhenFolderHasThreeMp3Files_ThenLibraryHasThreeSongs) {
    EXPECT_EQ(musicLibrary->getSongs().size(), 3);
}

TEST_F(GivenMusicLibraryTest, WhenFolderHasMp3Files_ThenSongNamesAreLoaded) {
    const std::set<Song>& songs = musicLibrary->getSongs();
    bool aahateinFound = false;

    for (const Song& song : songs) {
        if (song.name == "Aahatein") {
            aahateinFound = true;
            break;
        }
    }

    EXPECT_TRUE(aahateinFound);
}

TEST_F(GivenMusicLibraryTest, WhenFolderHasMp3Files_ThenSongsAreSortedByName) {
    const std::set<Song>& songs = musicLibrary->getSongs();
    std::string previousName = "";
    bool isSorted = true;

    for (const Song& song : songs) 
    {
        if (song.name < previousName) 
        {
            isSorted = false;
            break;
        }
        previousName = song.name;
    }

    EXPECT_TRUE(isSorted);
}

TEST_F(GivenEmptyMusicLibraryTest, WhenFolderIsEmpty_ThenLibraryHasNoSongs) {
    EXPECT_TRUE(musicLibrary->getSongs().empty());
}

TEST_F(GivenInvalidFolderMusicLibraryTest, WhenFolderDoesNotExist_ThenLibraryHasNoSongs) {
    EXPECT_TRUE(musicLibrary->getSongs().empty());
}

// Find Song By Title

TEST_F(GivenMusicLibraryTest, WhenSearchingExistingSong_ThenReturnsSong) {
    const Song* foundSong = musicLibrary->findSongByTitle("Aahatein");
    ASSERT_NE(foundSong, nullptr);
    EXPECT_EQ(foundSong->name, "Aahatein");
}

TEST_F(GivenMusicLibraryTest, WhenSearchingNonExistentSong_ThenReturnsNull) {
    const Song* foundSong = musicLibrary->findSongByTitle("NonExistentSong");
    EXPECT_EQ(foundSong, nullptr);
}

TEST_F(GivenEmptyMusicLibraryTest, WhenSearchingInEmptyLibrary_ThenReturnsNull) {
    const Song* foundSong = musicLibrary->findSongByTitle("Aahatein");
    EXPECT_EQ(foundSong, nullptr);
}

TEST_F(GivenInvalidFolderMusicLibraryTest, WhenSearchingInInvalidFolderLibrary_ThenReturnsNull) {
    const Song* foundSong = musicLibrary->findSongByTitle("Aahatein");
    EXPECT_EQ(foundSong, nullptr);
}

// Song in sub folders

TEST_F(GivenMusicLibraryTest, WhenFolderHasSubfolderWithMp3_ThenSongIsLoaded) {
    std::filesystem::create_directory("TestSongs/Subfolder");
    std::ofstream("TestSongs/Subfolder/SubSong.mp3").close();

    MusicLibrary libraryWithSubfolder("TestSongs");
    const Song* foundSong = libraryWithSubfolder.findSongByTitle("SubSong");

    ASSERT_NE(foundSong, nullptr);
    EXPECT_EQ(foundSong->name, "SubSong");

    std::filesystem::remove_all("TestSongs/Subfolder");
}

TEST_F(GivenMusicLibraryTest, WhenFolderHasNonMp3Files_ThenTheyAreNotLoaded) {
    std::ofstream("TestSongs/NotASong.txt").close();
    MusicLibrary libraryWithTxt("TestSongs");
    const Song* foundSong = libraryWithTxt.findSongByTitle("NotASong");
    EXPECT_EQ(foundSong, nullptr);
    std::filesystem::remove("TestSongs/NotASong.txt");
}
