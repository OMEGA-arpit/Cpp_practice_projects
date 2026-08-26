#ifndef I_MOCK_INPUT_HANDLER_H
#define I_MOCK_INPUT_HANDLER_H

#include <gmock/gmock.h>
#include "IInputHandler.h"

class IMockInputHandler : public IInputHandler {
public:
    MOCK_METHOD(int, inputValue, (), (override));
    MOCK_METHOD(void, inputString, (std::string& input), (override));
    MOCK_METHOD(char, inputCharacter, (), (override));
};

#endif
