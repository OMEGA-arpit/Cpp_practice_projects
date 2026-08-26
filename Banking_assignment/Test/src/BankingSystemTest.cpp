#include "BankingSystemTest.h"

TEST_F(GivenBankingSystemTest, WhenExecute_ThenCallsHandleMenuOnce) {
    EXPECT_CALL(mockBank, handleMenu())
        .Times(1);

    system.execute();
}
