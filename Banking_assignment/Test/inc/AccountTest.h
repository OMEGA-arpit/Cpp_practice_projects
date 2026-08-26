#ifndef ACCOUNT_TEST_H
#define ACCOUNT_TEST_H

#include "Account.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class GivenAccountTest : public ::testing::Test {
protected:
    Account account;

    void SetUp() override {
        std::string accountNumber = "12345678";
        account.setAccountNumber(accountNumber);
        account.setPin("4321");
        account.setBalance(1000.0);
    }
};

class GivenAccountInvalidAmountTest : public GivenAccountTest,
    public ::testing::WithParamInterface<double> {};

#endif
