#ifndef BANK_TEST_H
#define BANK_TEST_H

#include "Bank.h"
#include "MockLoginHandler.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class GivenBankTest : public ::testing::Test {
protected:
    MockLoginHandler mockAdminLogin;
    MockLoginHandler mockCustomerLogin;
    Bank bank{&mockAdminLogin, &mockCustomerLogin};
};

#endif
