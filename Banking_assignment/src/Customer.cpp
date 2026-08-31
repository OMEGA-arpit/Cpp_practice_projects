#include "Customer.h"
#include "Constants.h"
#include "Display.h"
#include "Messages.h"

void Customer::displayInformation() const {
    Display::printWithValue(Messages::MSG_DISPLAY_CUSTOMER_NAME, name);
    Display::printWithValue(Messages::MSG_DISPLAY_EMAIL, email);
    Display::printWithValue(Messages::MSG_DISPLAY_PHONE, phone);
    Display::printWithValue(Messages::MSG_DISPLAY_ACCOUNT_NUMBER, account.getAccountNumber());
}

void Customer::displayAccountDetails() const {
    Display::printWithValue(Messages::MSG_DISPLAY_ACCOUNT_NUMBER, account.getAccountNumber());
    Display::printWithAmount(Messages::MSG_DISPLAY_BALANCE, account.getBalance());
}
