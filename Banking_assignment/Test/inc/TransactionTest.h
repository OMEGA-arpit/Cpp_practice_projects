#ifndef TRANSACTION_TEST_H
#define TRANSACTION_TEST_H

#include "Transaction.h"
#include <gtest/gtest.h>

class GivenTransactionTest : public ::testing::Test {
protected:
    Transaction deposit{Constants::TransactionType::DEPOSIT, 500.0, 1500.0};
    Transaction withdrawal{Constants::TransactionType::WITHDRAWAL, 200.0, 800.0};
};

#endif
