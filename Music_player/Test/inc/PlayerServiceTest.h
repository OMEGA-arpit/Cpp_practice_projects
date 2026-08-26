#ifndef PLAYER_SERVICE_TEST_H
#define PLAYER_SERVICE_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PlayerService.h"
#include "IMockMusicLibrary.h"
#include "IMockAudioPlayer.h"
#include "IMockPersistenceManager.h"
#include "IMockPlaylistFactory.h"
#include "IMockPlaylist.h"

class GivenPlayerServiceTest : public ::testing::Test {
protected:
    testing::NiceMock<IMockMusicLibrary>* mockMusicLibrary;
    testing::NiceMock<IMockAudioPlayer>* mockAudioPlayer;
    testing::NiceMock<IMockPersistenceManager>* mockPersistenceManager;
    testing::NiceMock<IMockPlaylistFactory>* mockPlaylistFactory;
    PlayerService* playerService;

    void SetUp() override;
    void TearDown() override;
};

#endif
