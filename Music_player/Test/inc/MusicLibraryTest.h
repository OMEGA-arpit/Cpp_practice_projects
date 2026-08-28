#ifndef MUSIC_LIBRARY_TEST_H
#define MUSIC_LIBRARY_TEST_H

#include <gtest/gtest.h>
#include "MusicLibrary.h"

class GivenMusicLibraryTest : public ::testing::Test {
protected:
    MusicLibrary* musicLibrary;
    void SetUp() override;
    void TearDown() override;
};

class GivenEmptyMusicLibraryTest : public ::testing::Test {
protected:
    MusicLibrary* musicLibrary;
    void SetUp() override;
    void TearDown() override;
};

class GivenInvalidFolderMusicLibraryTest : public ::testing::Test {
protected:
    MusicLibrary* musicLibrary;
    void SetUp() override;
    void TearDown() override;
};

#endif
