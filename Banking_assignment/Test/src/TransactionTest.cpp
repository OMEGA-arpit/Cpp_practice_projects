#include "TransactionTest.h"
#include "Constants.h"

// Constructor Test
TEST_F(GivenTransactionTest, WhenConstructorCalled_ThenTypeSetCorrectly) {
    EXPECT_EQ(deposit.getType(), Constants::TransactionType::DEPOSIT);
}

TEST_F(GivenTransactionTest, WhenConstructorCalled_ThenAmountSetCorrectly) {
    EXPECT_DOUBLE_EQ(deposit.getAmount(), 500.0);
}

TEST_F(GivenTransactionTest, WhenConstructorCalled_ThenPostBalanceSetCorrectly) {
    EXPECT_DOUBLE_EQ(deposit.getPostBalance(), 1500.0);
}

// ID Counter
TEST_F(GivenTransactionTest, WhenTransactionId_ThenIsAtLeastInitialValue) {
    EXPECT_GE(deposit.getId(), Constants::INITIAL_TRANSACTION_ID);
}

TEST_F(GivenTransactionTest, WhenConsecutiveTransactionsId_ThenIncrementByOne) {
    EXPECT_EQ(withdrawal.getId(), deposit.getId() + 1);
}

// PostBalance
TEST_F(GivenTransactionTest, WhenSetPostBalance_ThenUpdatesPostBalance) {
    deposit.setPostBalance(2000.0);
    EXPECT_DOUBLE_EQ(deposit.getPostBalance(), 2000.0);
}
