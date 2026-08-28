#ifndef I_MOCK_USER_CONTROLLER_H
#define I_MOCK_USER_CONTROLLER_H

#include <gmock/gmock.h>
#include "IUserController.h"

class IMockUserController : public IUserController {
public:
    MOCK_METHOD(void, handleUserQueries, (), (override));
};

#endif
