#ifndef PERSISTENCE_MANAGER_TEST_H
#define PERSISTENCE_MANAGER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PersistenceManager.h"
#include "IMockLogger.h"
#include "IMockPlaylist.h"
#include "IMockPlaylistFactory.h"

class GivenPersistenceManagerTest : public ::testing::Test {
protected:
    IMockLogger mockLogger;
    PersistenceManager* persistenceManager;
    std::string testFilePath;

    void SetUp() override;
    void TearDown() override;
};

#endif
