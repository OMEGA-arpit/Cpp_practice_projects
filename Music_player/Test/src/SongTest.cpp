#include "SongTest.h"

void GivenSongTest::SetUp() {
    songOne = Song("Aahatein", "Songs/Aahatein.mp3");
    songTwo = Song("Believer", "Songs/Believer.mp3");
    songThree = Song("Aahatein", "Songs/Aahatein.mp3");
}

// Operator<

TEST_F(GivenSongTest, WhenFirstSongNameIsSmaller_ThenFirstSongIsLessThanSecond) {
    bool result = songOne < songTwo;
    EXPECT_TRUE(result);
}

TEST_F(GivenSongTest, WhenFirstSongNameIsLarger_ThenFirstSongIsNotLessThanSecond) {
    bool result = songTwo < songOne;
    EXPECT_FALSE(result);
}

TEST_F(GivenSongTest, WhenTwoSongsHaveSameName_ThenNeitherIsLessThanOther) {
    bool firstLessThanThird = songOne < songThree;
    bool thirdLessThanFirst = songThree < songOne;
    EXPECT_FALSE(firstLessThanThird);
    EXPECT_FALSE(thirdLessThanFirst);
}

TEST_F(GivenSongTest, WhenSongComparedWithItself_ThenNotLessThanItself) {
    bool result = songOne < songOne;
    EXPECT_FALSE(result);
}

// Operator ==

TEST_F(GivenSongTest, WhenTwoSongsHaveSameNameAndSamePath_ThenTheyAreEqual) {
    EXPECT_TRUE(songOne == songThree);
}

TEST_F(GivenSongTest, WhenTwoSongsHaveSameNameButDifferentPath_ThenTheyAreNotEqual) {
    Song songWithDifferentPath("Aahatein", "Songs/AnotherFolder/Aahatein.mp3");
    EXPECT_FALSE(songOne == songWithDifferentPath);
}

TEST_F(GivenSongTest, WhenTwoSongsHaveDifferentName_ThenTheyAreNotEqual) {
    EXPECT_FALSE(songOne == songTwo);
}
