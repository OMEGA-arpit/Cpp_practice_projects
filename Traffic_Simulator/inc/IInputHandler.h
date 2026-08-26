#ifndef I_INPUT_HANDLER_H
#define I_INPUT_HANDLER_H

#include <string>

class IInputHandler {
public:
    virtual void inputString(std::string& input) = 0;  
     
    virtual ~IInputHandler() {}                       
};

#endif
