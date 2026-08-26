#include "AdminLoginHandler.h"
#include "Display.h"
#include "Messages.h"
#include "InputHandler.h"

bool AdminLoginHandler::getAndVerifyCredentials() {
    std::string userName;
    Display::printMessage(Messages::MSG_ENTER_USERNAME);
    InputHandler::inputString(userName, Constants::InputType::USERNAME);

    std::string password;
    Display::printMessage(Messages::MSG_ENTER_PASSWORD);
    InputHandler::inputString(password, Constants::InputType::PASSWORD);

    return admin.authenticate(userName, password);
}

Constants::LoginResult AdminLoginHandler::login() {
    Constants::LoginResult result = Constants::LoginResult::FAILED;

    Display::printMessage(Messages::MSG_ADMIN_LOGIN);

    if (getAndVerifyCredentials())
    {
        result = Constants::LoginResult::SUCCESS;
        Display::printMessage(Messages::MSG_LOGIN_SUCCESS);
        if (!adminController->handleMenu())
        {
            logout();
        }
    }

    return result;
}

void AdminLoginHandler::logout() {
    Display::clearScreen();
    Display::printMessage(Messages::MSG_LOGOUT);
}
