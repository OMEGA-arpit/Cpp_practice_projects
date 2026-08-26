#include "PlaylistTest.h"

void GivenPlaylistTest::SetUp() {
    playlist = Playlist("Test Playlist");
    songOne = Song("Aahatein", "Songs/Aahatein.mp3");
    songTwo = Song("Believer", "Songs/Believer.mp3");
    songThree = Song("Tum Hi Ho", "Songs/TumHiHo.mp3");
}

// Add Song

TEST_F(GivenPlaylistTest, WhenSongAdded_ThenReturnsTrue) {
    bool result = playlist.addSong(songOne);
    EXPECT_TRUE(result);
}

TEST_F(GivenPlaylistTest, WhenSongAdded_ThenPlaylistHasOneSong) {
    playlist.addSong(songOne);
    EXPECT_EQ(playlist.getSongs().size(), 1);
}

TEST_F(GivenPlaylistTest, WhenSameSongAddedAgain_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.addSong(songOne);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlaylistTest, WhenSameSongAddedAgain_ThenSizeRemainsOne) {
    playlist.addSong(songOne);
    playlist.addSong(songOne);
    EXPECT_EQ(playlist.getSongs().size(), 1);
}

TEST_F(GivenPlaylistTest, WhenFirstSongAdded_ThenCurrentSongIsAddedSong) {
    playlist.addSong(songOne);
    Song* currentSong = playlist.getCurrentSong();
    ASSERT_NE(currentSong, nullptr);
    EXPECT_EQ(currentSong->name, songOne.name);
}

TEST_F(GivenPlaylistTest, WhenTwoDifferentSongsAdded_ThenSizeIsTwo) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    EXPECT_EQ(playlist.getSongs().size(), 2);
}

// Remove Song

TEST_F(GivenPlaylistTest, WhenExistingSongRemoved_ThenReturnsTrue) {
    playlist.addSong(songOne);
    bool result = playlist.removeSong(songOne.name);
    EXPECT_TRUE(result);
}

TEST_F(GivenPlaylistTest, WhenOnlySongRemoved_ThenPlaylistIsEmpty) {
    playlist.addSong(songOne);
    playlist.removeSong(songOne.name);
    EXPECT_TRUE(playlist.getSongs().empty());
}

TEST_F(GivenPlaylistTest, WhenSongRemovedFromEmptyPlaylist_ThenReturnsFalse) {
    bool result = playlist.removeSong(songOne.name);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlaylistTest, WhenNonExistentSongRemoved_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.removeSong(songTwo.name);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlaylistTest, WhenCurrentSongRemoved_ThenCurrentSongUpdatesToNext) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    playlist.removeSong(songOne.name);

    Song* currentSong = playlist.getCurrentSong();
    ASSERT_NE(currentSong, nullptr);
    EXPECT_EQ(currentSong->name, songTwo.name);
}

TEST_F(GivenPlaylistTest, WhenOnlySongRemoved_ThenCurrentSongIsNull) {
    playlist.addSong(songOne);
    playlist.removeSong(songOne.name);
    EXPECT_EQ(playlist.getCurrentSong(), nullptr);
}

// Get Current Song

TEST_F(GivenPlaylistTest, WhenPlaylistIsEmpty_ThenCurrentSongIsNull) {
    EXPECT_EQ(playlist.getCurrentSong(), nullptr);
}

TEST_F(GivenPlaylistTest, WhenSongAdded_ThenCurrentSongIsFirstSong) {
    playlist.addSong(songOne);
    Song* currentSong = playlist.getCurrentSong();
    ASSERT_NE(currentSong, nullptr);
    EXPECT_EQ(currentSong->name, songOne.name);
}

// Next Song

TEST_F(GivenPlaylistTest, WhenPlaylistIsEmpty_ThenNextSongIsNull) {
    EXPECT_EQ(playlist.nextSong(), nullptr);
}

TEST_F(GivenPlaylistTest, WhenNextSongCalled_ThenReturnsSecondSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    Song* nextSong = playlist.nextSong();
    ASSERT_NE(nextSong, nullptr);
    EXPECT_EQ(nextSong->name, songTwo.name);
}

TEST_F(GivenPlaylistTest, WhenAtLastSong_ThenNextSongWrapsToFirstSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    playlist.nextSong();
    Song* wrappedSong = playlist.nextSong();
    ASSERT_NE(wrappedSong, nullptr);
    EXPECT_EQ(wrappedSong->name, songOne.name);
}

TEST_F(GivenPlaylistTest, WhenOnlyOneSong_ThenNextSongWrapsToSameSong) {
    playlist.addSong(songOne);
    Song* nextSong = playlist.nextSong();
    ASSERT_NE(nextSong, nullptr);
    EXPECT_EQ(nextSong->name, songOne.name);
}

// Previous Song

TEST_F(GivenPlaylistTest, WhenPlaylistIsEmpty_ThenPreviousSongIsNull) {
    EXPECT_EQ(playlist.previousSong(), nullptr);
}

TEST_F(GivenPlaylistTest, WhenAtFirstSong_ThenPreviousSongWrapsToLastSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    Song* previousSong = playlist.previousSong();
    ASSERT_NE(previousSong, nullptr);
    EXPECT_EQ(previousSong->name, songTwo.name);
}

TEST_F(GivenPlaylistTest, WhenAtSecondSong_ThenPreviousSongReturnsFirstSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    playlist.nextSong();
    Song* previousSong = playlist.previousSong();
    ASSERT_NE(previousSong, nullptr);
    EXPECT_EQ(previousSong->name, songOne.name);
}

TEST_F(GivenPlaylistTest, WhenOnlyOneSong_ThenPreviousSongWrapsToSameSong) {
    playlist.addSong(songOne);
    Song* previousSong = playlist.previousSong();
    ASSERT_NE(previousSong, nullptr);
    EXPECT_EQ(previousSong->name, songOne.name);
}

// Search Song

TEST_F(GivenPlaylistTest, WhenSearchingExistingSong_ThenReturnsSong) {
    playlist.addSong(songOne);
    Song* foundSong = playlist.searchSong(songOne.name);
    ASSERT_NE(foundSong, nullptr);
    EXPECT_EQ(foundSong->name, songOne.name);
}

TEST_F(GivenPlaylistTest, WhenSearchingNonExistentSong_ThenReturnsNull) {
    playlist.addSong(songOne);
    Song* foundSong = playlist.searchSong(songTwo.name);
    EXPECT_EQ(foundSong, nullptr);
}

TEST_F(GivenPlaylistTest, WhenSearchingInEmptyPlaylist_ThenReturnsNull) {
    Song* foundSong = playlist.searchSong(songOne.name);
    EXPECT_EQ(foundSong, nullptr);
}

// Move Song Upward

TEST_F(GivenPlaylistTest, WhenSecondSongMovedUpward_ThenReturnsTrue) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    bool result = playlist.moveSongUpward(songTwo.name);
    EXPECT_TRUE(result);
}

TEST_F(GivenPlaylistTest, WhenSecondSongMovedUpward_ThenBecomesFirstSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    playlist.moveSongUpward(songTwo.name);
    EXPECT_EQ(playlist.getSongs().front().name, songTwo.name);
}

TEST_F(GivenPlaylistTest, WhenFirstSongMovedUpward_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.moveSongUpward(songOne.name);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlaylistTest, WhenNonExistentSongMovedUpward_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.moveSongUpward(songTwo.name);
    EXPECT_FALSE(result);
}

// Move Song Downward

TEST_F(GivenPlaylistTest, WhenFirstSongMovedDownward_ThenReturnsTrue) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    bool result = playlist.moveSongDownward(songOne.name);
    EXPECT_TRUE(result);
}

TEST_F(GivenPlaylistTest, WhenFirstSongMovedDownward_ThenBecomesLastSong) {
    playlist.addSong(songOne);
    playlist.addSong(songTwo);
    playlist.moveSongDownward(songOne.name);
    EXPECT_EQ(playlist.getSongs().back().name, songOne.name);
}

TEST_F(GivenPlaylistTest, WhenLastSongMovedDownward_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.moveSongDownward(songOne.name);
    EXPECT_FALSE(result);
}

TEST_F(GivenPlaylistTest, WhenNonExistentSongMovedDownward_ThenReturnsFalse) {
    playlist.addSong(songOne);
    bool result = playlist.moveSongDownward(songTwo.name);
    EXPECT_FALSE(result);
}
