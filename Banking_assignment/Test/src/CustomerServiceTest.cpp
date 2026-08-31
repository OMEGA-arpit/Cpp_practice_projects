#include "CustomerServiceTest.h"
#include <cctype>

// Create Customer Test

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenNameSetCorrectly) {
    EXPECT_EQ(customer->getName(), "Daksh Sharma");
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenEmailSetCorrectly) {
    EXPECT_EQ(customer->getEmail(), "daksh@gmail.com");
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenPhoneSetCorrectly) {
    EXPECT_EQ(customer->getPhone(), "1234567890");
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenInitialBalanceZero) {
    EXPECT_DOUBLE_EQ(customer->getAccount().getBalance(), 0.0);
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenAddsToCustomers) {
    EXPECT_THAT(service.getCustomers(), ::testing::SizeIs(1));
}

TEST_F(GivenCustomerServiceTest, WhenCreateMultipleCustomers_ThenAllAdded) {
    service.createCustomer("Disha Jain", "jain@email.com", "0987654321");
    EXPECT_THAT(service.getCustomers(), ::testing::SizeIs(2));
}

TEST_F(GivenCustomerServiceTest, WhenCreateMultipleCustomers_ThenAccountNumbersIncrement) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    auto result = service.createCustomer("Disha Jain", "jain@email.com", "0987654321");
    long accountNumber1 = std::stol(accountNumber);
    long accountNumber2 = std::stol(result.customer->getAccount().getAccountNumber());
    EXPECT_EQ(accountNumber2, accountNumber1 + 1);
}

// Find Customer Test

TEST_F(GivenCustomerServiceTest, WhenFindExistingAccountNumber_ThenReturnsNonNullptr) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    EXPECT_NE(service.findCustomerByAccountNumber(accountNumber), nullptr);
}

TEST_F(GivenCustomerServiceTest, WhenFindExistingAccountNumber_ThenReturnsCorrectCustomer) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    Customer* found = service.findCustomerByAccountNumber(accountNumber);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Daksh Sharma");
}

TEST_F(GivenCustomerServiceTest, WhenFindNonExistingAccountNumber_ThenReturnsNullptr) {
    EXPECT_EQ(service.findCustomerByAccountNumber("0000000"), nullptr);
}

TEST_F(GivenCustomerServiceTest, WhenFindAmongMultipleCustomers_ThenFindsCorrectOne) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    service.createCustomer("Disha Jain", "jain@email.com", "0987654321");
    Customer* found = service.findCustomerByAccountNumber(accountNumber);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Daksh Sharma");
}

// Delete Customer

TEST_F(GivenCustomerServiceTest, WhenDeleteExistingCustomer_ThenReturnsTrue) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    EXPECT_TRUE(service.deleteCustomerFromBank(accountNumber));
}

TEST_F(GivenCustomerServiceTest, WhenDeleteExistingCustomer_ThenRemovesFromList) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    service.deleteCustomerFromBank(accountNumber);
    EXPECT_THAT(service.getCustomers(), ::testing::IsEmpty());
}

TEST_F(GivenCustomerServiceTest, WhenDeleteExistingCustomer_ThenCanNoLongerBeFound) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    service.deleteCustomerFromBank(accountNumber);
    EXPECT_EQ(service.findCustomerByAccountNumber(accountNumber), nullptr);
}

TEST_F(GivenCustomerServiceTest, WhenDeleteNonExistingCustomer_ThenReturnsFalse) {
    EXPECT_FALSE(service.deleteCustomerFromBank("0000000"));
}

TEST_F(GivenCustomerServiceTest, WhenDeleteAmongMultipleCustomers_ThenOnlyTargetRemoved) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    service.createCustomer("Disha Jain", "jain@email.com", "0987654321");
    service.deleteCustomerFromBank(accountNumber);
    EXPECT_THAT(service.getCustomers(), ::testing::SizeIs(1));
    EXPECT_EQ(service.getCustomers().front().getName(), "Disha Jain");
}

TEST_F(GivenCustomerServiceTest, WhenDeleteCustomerWithPositiveBalance_ThenReturnsFalse) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    customer->getAccount().setBalance(500.0);
    EXPECT_FALSE(service.deleteCustomerFromBank(accountNumber));
}

// Registration Result Tests

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenAccountNumberMatchesStoredAccount) {
    // Arrange / Act
    auto result = service.createCustomer("Jane Doe", "jane@example.com", "5555555555");

    // Assert
    EXPECT_EQ(result.customer->getAccount().getAccountNumber(), result.accountNumber);
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenGeneratedPinHasFourDigits) {
    auto result = service.createCustomer("Jane Doe", "jane@example.com", "5555555555");

    EXPECT_EQ(result.pin.size(), static_cast<size_t>(Constants::PIN_LENGTH));
}

TEST_F(GivenCustomerServiceTest, WhenCreateCustomer_ThenGeneratedPinContainsOnlyDigits) {
    auto result = service.createCustomer("Jane Doe", "jane@example.com", "5555555555");

    for (char c : result.pin) {
        EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(c)))
            << "Non-digit character '" << c << "' found in generated PIN";
    }
}

TEST_F(GivenCustomerServiceTest, WhenDeleteCustomerWithPositiveBalance_ThenCustomerStillExists) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    customer->getAccount().setBalance(500.0);
    service.deleteCustomerFromBank(accountNumber);
    EXPECT_NE(service.findCustomerByAccountNumber(accountNumber), nullptr);
}

TEST_F(GivenCustomerServiceTest, WhenDeleteCustomerWithZeroBalance_ThenReturnsTrue) {
    std::string accountNumber = customer->getAccount().getAccountNumber();
    EXPECT_TRUE(service.deleteCustomerFromBank(accountNumber));
}
