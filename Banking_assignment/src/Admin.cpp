#include "Admin.h"
#include "Display.h"
#include "Messages.h"

void Admin::displayInformation() const {
    Display::printWithValue(Messages::MSG_DISPLAY_ADMIN_NAME, name);
    Display::printWithValue(Messages::MSG_DISPLAY_USERNAME, userName);
}
