#ifndef BANKING_SYSTEM_TEST_H
#define BANKING_SYSTEM_TEST_H

#include "BankingSystem.h"
#include "MockBank.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class GivenBankingSystemTest : public ::testing::Test {
protected:
    MockBank mockBank;
    BankingSystem system{&mockBank};
};

#endif
