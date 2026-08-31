#ifndef MOCK_BANK_H
#define MOCK_BANK_H

#include "IBank.h"
#include <gmock/gmock.h>

class MockBank : public IBank {
public:
    MOCK_METHOD(void, handleMenu, (), (override));
    MOCK_METHOD(bool, login, (Constants::UserRole), (override));
};

#endif
