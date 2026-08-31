#include "CustomerTest.h"

// Getters Test

TEST_F(GivenCustomerTest, WhenConstructor_ThenNameSetCorrectly) {
    EXPECT_EQ(customer.getName(), "Daksh Sharma");
}

TEST_F(GivenCustomerTest, WhenConstructor_ThenEmailSetCorrectly) {
    EXPECT_EQ(customer.getEmail(), "daksh@gmail.com");
}

TEST_F(GivenCustomerTest, WhenConstructor_ThenPhoneSetCorrectly) {
    EXPECT_EQ(customer.getPhone(), "6789543210");
}

TEST_F(GivenCustomerTest, WhenConstructor_ThenRoleSetToCustomer) {
    EXPECT_EQ(customer.getRole(), Constants::UserRole::CUSTOMER);
}

// Setters Test

TEST_F(GivenCustomerTest, WhenSetEmail_ThenUpdatesEmail) {
    customer.setEmail("new@email.com");
    EXPECT_EQ(customer.getEmail(), "new@email.com");
}

TEST_F(GivenCustomerTest, WhenSetPhone_ThenUpdatesPhone) {
    customer.setPhone("0987654321");
    EXPECT_EQ(customer.getPhone(), "0987654321");
}

TEST_F(GivenCustomerTest, WhenSetName_ThenUpdatesName) {
    std::string newName = "Disha Sharma";
    customer.setName(newName);
    EXPECT_EQ(customer.getName(), newName);
}

TEST_F(GivenCustomerTest, WhenGetAccount_ThenReturnsReference) {
    customer.getAccount().deposit(500.0);
    EXPECT_DOUBLE_EQ(customer.getAccount().getBalance(), 500.0);
}

// Authentication Test

TEST_F(GivenCustomerTest, WhenCorrectCredentials_ThenAuthenticateReturnsTrue) {
    EXPECT_TRUE(customer.authenticate("12345678", "4321"));
}

TEST_F(GivenCustomerTest, WhenWrongAccountNumber_ThenAuthenticateReturnsFalse) {
    EXPECT_FALSE(customer.authenticate("00000000", "4321"));
}

TEST_F(GivenCustomerTest, WhenWrongPin_ThenAuthenticateReturnsFalse) {
    EXPECT_FALSE(customer.authenticate("12345678", "0000"));
}

TEST_F(GivenCustomerTest, WhenBothWrong_ThenAuthenticateReturnsFalse) {
    EXPECT_FALSE(customer.authenticate("00000000", "0000"));
}

