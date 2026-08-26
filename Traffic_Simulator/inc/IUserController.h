#ifndef I_USER_CONTROLLER_H
#define I_USER_CONTROLLER_H

class IUserController {
public:
    virtual void handleUserQueries() = 0;
    virtual ~IUserController() {}
};

#endif
