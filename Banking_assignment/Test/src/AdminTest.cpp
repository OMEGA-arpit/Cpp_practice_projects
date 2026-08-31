#include "AdminTest.h"
#include "Constants.h"

// Constructor Tests

TEST_F(GivenAdminTest, WhenConstructorCalled_ThenNameSetCorrectly) {
    EXPECT_EQ(admin.getName(), Constants::ADMIN_NAME);
}

TEST_F(GivenAdminTest, WhenConstructorCalled_ThenRoleSetCorrectly) {
    EXPECT_EQ(admin.getRole(), Constants::UserRole::ADMIN);
}

// Authenticate Admin

TEST_F(GivenAdminTest, WhenCorrectCredentials_ThenAuthenticateReturnsTrue) {
    EXPECT_TRUE(admin.authenticate(Constants::ADMIN_USERNAME, Constants::ADMIN_PASSWORD));
}

TEST_F(GivenAdminTest, WhenWrongUsername_ThenAuthenticateReturnsFalse) {
    std::string input = "wrong";
    EXPECT_FALSE(admin.authenticate(input, Constants::ADMIN_PASSWORD));
}

TEST_F(GivenAdminTest, WhenWrongPassword_ThenAuthenticateReturnsFalse) {
    std::string input = "wrong";
    EXPECT_FALSE(admin.authenticate(Constants::ADMIN_USERNAME, input));
}

TEST_F(GivenAdminTest, WhenBothWrong_ThenAuthenticateReturnsFalse) {
    std::string username = "wrong";
    std::string password = "wrong";
    EXPECT_FALSE(admin.authenticate(username, password));
}

// Getters/Setters

TEST_F(GivenAdminTest, WhenSetName_ThenUpdatesName) {
    std::string newName = "New Admin";
    admin.setName(newName);
    EXPECT_EQ(admin.getName(), newName);
}
