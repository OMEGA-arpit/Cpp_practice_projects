#include "AccountTest.h"

// Constructor Test

TEST_F(GivenAccountTest, WhenConstructorCalled_ThenBalanceInitializedToZero) {
    Account freshAccount;
    EXPECT_DOUBLE_EQ(freshAccount.getBalance(), 0.0);
}

// Setter/Getter Test

TEST_F(GivenAccountTest, WhenSetAccountNumber_ThenUpdatedAccountNumber) {
    std::string newNumber = "99999999";
    account.setAccountNumber(newNumber);
    EXPECT_EQ(account.getAccountNumber(), "99999999");
}

TEST_F(GivenAccountTest, WhenSetValidBalance_ThenUpdatedBalance) {
    account.setBalance(500.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 500.0);
}

TEST_F(GivenAccountTest, WhenSetInvalidBalance_ThenBalanceUnchanged) {
    account.setBalance(-100.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 1000.0);
}

// Verify Pin

TEST_F(GivenAccountTest, WhenVerifyCorrectPin_ThenReturnsTrue) {
    EXPECT_TRUE(account.verifyPin("4321"));
}

TEST_F(GivenAccountTest, WhenVerifyIncorrectPin_ThenReturnsFalse) {
    EXPECT_FALSE(account.verifyPin("0000"));
}

// Deposit Test

TEST_F(GivenAccountTest, WhenDepositValidAmount_ThenBalanceIncreases) {
    account.deposit(500.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 1500.0);
}

TEST_F(GivenAccountTest, WhenDepositValidAmount_ThenTransactionRecorded) {
    account.deposit(500.0);
    ASSERT_EQ(account.getTransactions().size(), 1);
    EXPECT_EQ(account.getTransactions().back().getType(), Constants::TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(account.getTransactions().back().getAmount(), 500.0);
    EXPECT_DOUBLE_EQ(account.getTransactions().back().getPostBalance(), 1500.0);
}

// Withdrawal Test

TEST_F(GivenAccountTest, WhenWithdrawalValidAmount_ThenBalanceDecreases) {
    account.withdrawal(200.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 800.0);
}

TEST_F(GivenAccountTest, WhenWithdrawalValidAmount_ThenTransactionRecorded) {
    account.withdrawal(200.0);
    ASSERT_EQ(account.getTransactions().size(), 1);
    EXPECT_EQ(account.getTransactions().back().getType(), Constants::TransactionType::WITHDRAWAL);
    EXPECT_DOUBLE_EQ(account.getTransactions().back().getAmount(), 200.0);
    EXPECT_DOUBLE_EQ(account.getTransactions().back().getPostBalance(), 800.0);
}

TEST_F(GivenAccountTest, WhenWithdrawalExactBalance_ThenBalanceBecomesZero) {
    account.withdrawal(1000.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 0.0);
}

TEST_F(GivenAccountTest, WhenWithdrawalInsufficientBalance_ThenReturnsFalse) {
    EXPECT_FALSE(account.withdrawal(1500.0));
}

TEST_F(GivenAccountTest, WhenWithdrawalInsufficientBalance_ThenBalanceUnchanged) {
    account.withdrawal(1500.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 1000.0);
}

TEST_F(GivenAccountTest, WhenWithdrawalInsufficientBalance_ThenNoTransactionRecorded) {
    account.withdrawal(1500.0);
    EXPECT_THAT(account.getTransactions(), ::testing::IsEmpty());
}

// Invalid Transaction Limits for Deposit and Withdraw

INSTANTIATE_TEST_SUITE_P(InvalidAmounts, GivenAccountInvalidAmountTest,
    ::testing::Values(
        Constants::MIN_TRANSACTION_AMOUNT - 1,
        Constants::MAX_TRANSACTION_AMOUNT + 1
    )
);

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidDepositAmount_ThenReturnsFalse) {
    EXPECT_FALSE(account.deposit(GetParam()));
}

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidDepositAmount_ThenBalanceUnchanged) {
    account.deposit(GetParam());
    EXPECT_DOUBLE_EQ(account.getBalance(), 1000.0);
}

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidDepositAmount_ThenNoTransactionRecorded) {
    account.deposit(GetParam());
    EXPECT_THAT(account.getTransactions(), ::testing::IsEmpty());
}

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidWithdrawalAmount_ThenReturnsFalse) {
    EXPECT_FALSE(account.withdrawal(GetParam()));
}

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidWithdrawalAmount_ThenBalanceUnchanged) {
    account.withdrawal(GetParam());
    EXPECT_DOUBLE_EQ(account.getBalance(), 1000.0);
}

TEST_P(GivenAccountInvalidAmountTest, WhenInvalidWithdrawalAmount_ThenNoTransactionRecorded) {
    account.withdrawal(GetParam());
    EXPECT_THAT(account.getTransactions(), ::testing::IsEmpty());
}

// Get Last Transactions

TEST_F(GivenAccountTest, WhenEmptyAccountTransactions_ThenReturnsEmptyVector) {
    EXPECT_TRUE(account.getLastTransactions(5).empty());
}

TEST_F(GivenAccountTest, WhenFewerThanCountTransactions_ThenReturnsAll) {
    account.deposit(100.0);
    account.deposit(200.0);
    EXPECT_EQ(account.getLastTransactions(5).size(), 2);
}

TEST_F(GivenAccountTest, WhenEqualToCountTransactions_ThenReturnsAll) {
    account.deposit(100.0);
    account.withdrawal(500.0);
    account.deposit(200.0);
    EXPECT_EQ(account.getLastTransactions(3).size(), 3);
}

TEST_F(GivenAccountTest, WhenMoreThanCountTransactions_ThenReturnLastTransactions) {
    account.deposit(100.0);
    account.withdrawal(500.0);
    account.deposit(200.0);

    std::vector<Transaction> result = account.getLastTransactions(2);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0].getAmount(), 500.0);
    EXPECT_DOUBLE_EQ(result[1].getAmount(), 200.0);
}

TEST_F(GivenAccountTest, WhenGetLastTransactionsCountZero_ThenReturnsEmptyVector) {
    account.deposit(500.0);
    EXPECT_TRUE(account.getLastTransactions(0).empty());
}

// Boundary value tests — exactly MIN and MAX transaction amounts are valid

TEST_F(GivenAccountTest, WhenDepositExactMinimumAmount_ThenSucceeds) {
    EXPECT_TRUE(account.deposit(Constants::MIN_TRANSACTION_AMOUNT));
}

TEST_F(GivenAccountTest, WhenDepositExactMaximumAmount_ThenSucceeds) {
    EXPECT_TRUE(account.deposit(Constants::MAX_TRANSACTION_AMOUNT));
}

TEST_F(GivenAccountTest, WhenWithdrawalExactMinimumAmount_ThenSucceeds) {
    EXPECT_TRUE(account.withdrawal(Constants::MIN_TRANSACTION_AMOUNT));
}

TEST_F(GivenAccountTest, WhenWithdrawalExactMaximumAmount_ThenSucceeds) {
    account.setBalance(Constants::MAX_TRANSACTION_AMOUNT);
    EXPECT_TRUE(account.withdrawal(Constants::MAX_TRANSACTION_AMOUNT));
}
