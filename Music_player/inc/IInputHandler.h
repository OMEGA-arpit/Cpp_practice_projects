#ifndef I_INPUT_HANDLER_H
#define I_INPUT_HANDLER_H

#include <string>

class IInputHandler {
public:
    virtual int inputValue() = 0;
    virtual char inputCharacter() = 0;     
    virtual void inputString(std::string& input) = 0;  
     
    virtual ~IInputHandler() {}                       
};

#endif
