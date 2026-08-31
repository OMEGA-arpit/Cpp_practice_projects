#include "BankTest.h"

// Admin Login

TEST_F(GivenBankTest, WhenAdminLoginSuccessOnFirstAttempt_ThenReturnsTrue) {
    EXPECT_CALL(mockAdminLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));

    EXPECT_TRUE(bank.login(Constants::UserRole::ADMIN));
}

TEST_F(GivenBankTest, WhenAdminLoginFailsThenSucceeds_ThenReturnsTrue) {
    EXPECT_CALL(mockAdminLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::FAILED))
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));

    EXPECT_TRUE(bank.login(Constants::UserRole::ADMIN));
}

TEST_F(GivenBankTest, WhenAdminLoginExhaustsAllAttempts_ThenReturnsFalse) {
    EXPECT_CALL(mockAdminLogin, login())
        .Times(Constants::MAX_LOGIN_ATTEMPTS)
        .WillRepeatedly(::testing::Return(Constants::LoginResult::FAILED));

    EXPECT_FALSE(bank.login(Constants::UserRole::ADMIN));
}

// Customer Login

TEST_F(GivenBankTest, WhenCustomerLoginSuccessOnFirstAttempt_ThenReturnsTrue) {
    EXPECT_CALL(mockCustomerLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));

    EXPECT_TRUE(bank.login(Constants::UserRole::CUSTOMER));
}

TEST_F(GivenBankTest, WhenCustomerLoginAccountNotFound_ThenReturnsTrueImmediately) {
    EXPECT_CALL(mockCustomerLogin, login())
        .Times(1)
        .WillOnce(::testing::Return(Constants::LoginResult::ACCOUNT_NOT_FOUND));

    EXPECT_TRUE(bank.login(Constants::UserRole::CUSTOMER));
}

TEST_F(GivenBankTest, WhenCustomerLoginExhaustsAllAttempts_ThenReturnsFalse) {
    EXPECT_CALL(mockCustomerLogin, login())
        .Times(Constants::MAX_LOGIN_ATTEMPTS)
        .WillRepeatedly(::testing::Return(Constants::LoginResult::FAILED));

    EXPECT_FALSE(bank.login(Constants::UserRole::CUSTOMER));
}

// Role Setup

TEST_F(GivenBankTest, WhenAdminRoleUsesAdminHandler_ThenNotCustomerHandler) {
    EXPECT_CALL(mockAdminLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));
    EXPECT_CALL(mockCustomerLogin, login())
        .Times(0);

    bank.login(Constants::UserRole::ADMIN);
}

TEST_F(GivenBankTest, WhenCustomerRoleUsesCustomerHandler_ThenNotAdminHandler) {
    EXPECT_CALL(mockCustomerLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));
    EXPECT_CALL(mockAdminLogin, login())
        .Times(0);

    bank.login(Constants::UserRole::CUSTOMER);
}

// Account Not Found

TEST_F(GivenBankTest, WhenAccountNotFound_ThenDoesNotCountAsFailedAttempt) {
    EXPECT_CALL(mockCustomerLogin, login())
        .Times(1)
        .WillOnce(::testing::Return(Constants::LoginResult::ACCOUNT_NOT_FOUND));

    bank.login(Constants::UserRole::CUSTOMER);
}

// Handle Choice Test
TEST_F(GivenBankTest, WhenChoiceIsOneAndAdminLoginSucceeds_ThenReturnsTrue) {
    EXPECT_CALL(mockAdminLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));

    EXPECT_TRUE(bank.handleChoice(1));
}

TEST_F(GivenBankTest, WhenChoiceIsTwoAndCustomerLoginSucceeds_ThenReturnsTrue) {
    EXPECT_CALL(mockCustomerLogin, login())
        .WillOnce(::testing::Return(Constants::LoginResult::SUCCESS));

    EXPECT_TRUE(bank.handleChoice(2));
}

TEST_F(GivenBankTest, WhenInvalidChoice_ThenReturnTrueAndNoLogin) {
    EXPECT_CALL(mockAdminLogin, login())
        .Times(0);
    EXPECT_CALL(mockCustomerLogin, login())
        .Times(0);

    EXPECT_TRUE(bank.handleChoice(99));
}

TEST_F(GivenBankTest, WhenChoiceIsOneAndAdminLoginFails_ThenReturnsFalse) {
    EXPECT_CALL(mockAdminLogin, login())
        .WillRepeatedly(::testing::Return(Constants::LoginResult::FAILED));

    EXPECT_FALSE(bank.handleChoice(1));
}

TEST_F(GivenBankTest, WhenChoiceTwoAndCustomerLoginFails_ThenReturnFalse) {
    EXPECT_CALL(mockCustomerLogin, login())
        .WillRepeatedly(::testing::Return(Constants::LoginResult::FAILED));

    EXPECT_FALSE(bank.handleChoice(2));
}

TEST_F(GivenBankTest, WhenChoiceThree_ThenReturnFalseAndNoLogin) {
    EXPECT_CALL(mockAdminLogin, login())
        .Times(0);

    EXPECT_CALL(mockCustomerLogin, login())
        .Times(0);

    EXPECT_FALSE(bank.handleChoice(3));
}
