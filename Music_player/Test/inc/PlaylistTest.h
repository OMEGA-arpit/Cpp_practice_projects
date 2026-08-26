#ifndef PLAYLIST_TEST_H
#define PLAYLIST_TEST_H

#include <gtest/gtest.h>
#include "Playlist.h"

class GivenPlaylistTest : public ::testing::Test {
protected:
    Playlist playlist;
    Song songOne;
    Song songTwo;
    Song songThree;

    void SetUp() override;
};

#endif
