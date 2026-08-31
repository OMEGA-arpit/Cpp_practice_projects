#include "ValidatorTest.h"
#include "Constants.h"

// ValidationResult struct tests

TEST(GivenValidationResultTest, WhenResultIsOk_ThenBoolConversionIsTrue) {
    auto result = ValidationResult::ok();
    EXPECT_TRUE(result);
    EXPECT_TRUE(result.valid);
    EXPECT_TRUE(result.errorMessage.empty());
}

TEST(GivenValidationResultTest, WhenResultIsFail_ThenBoolConversionIsFalse) {
    auto result = ValidationResult::fail("some error");
    EXPECT_FALSE(result);
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.errorMessage, "some error");
}

// Name Tests

TEST(GivenValidatorNameTest, WhenExactMinLengthAllAlpha_ThenReturnsTrue) {
    std::string input(Constants::MIN_NAME_LENGTH, 'A');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::NAME));
}

TEST(GivenValidatorNameTest, WhenAboveMinLengthWithSpace_ThenReturnsTrue) {
    std::string input(Constants::MIN_NAME_LENGTH + 1, 'A');
    input[Constants::MIN_NAME_LENGTH - 1] = ' ';
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::NAME));
}

TEST(GivenValidatorNameTest, WhenBelowMinLength_ThenReturnsFalse) {
    std::string input(Constants::MIN_NAME_LENGTH - 1, 'A');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::NAME));
}

TEST_P(GivenValidatorNameInvalidCharTest, WhenContainsInvalidChar_ThenReturnsFalse) {
    std::string input(Constants::MIN_NAME_LENGTH + 1, 'A');
    input[Constants::MIN_NAME_LENGTH - 1] = GetParam();
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::NAME));
}

INSTANTIATE_TEST_SUITE_P(InvalidChars, GivenValidatorNameInvalidCharTest,
    ::testing::Values('1', '@', '3')
);

// Email Tests

TEST(GivenValidatorEmailTest, WhenCorrectEmailFormat_ThenReturnsTrue) {
    std::string input = "hiya@gmail.com";
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::EMAIL));
}

TEST(GivenValidatorEmailTest, WhenEmailWithSubdomain_ThenReturnsTrue) {
    std::string input = "user@mail.company.com";
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::EMAIL));
}

TEST(GivenValidatorEmailTest, WhenEmailWithPlusAddressing_ThenReturnsTrue) {
    std::string input = "user+tag@gmail.com";
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::EMAIL));
}

TEST_P(GivenValidatorEmailInvalidFormatTest, WhenInvalidFormat_ThenReturnsFalse) {
    std::string input = GetParam();
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::EMAIL));
}

INSTANTIATE_TEST_SUITE_P(InvalidEmails, GivenValidatorEmailInvalidFormatTest,
    ::testing::Values("hiyagmail.com", "jain@gmailcom", "hiya@gmail.", 
                      "hiya@gmail@a.com", "daksh@@hoor.org", "daksh@hoor..g")
);

// Phone Number Tests

TEST(GivenValidatorPhoneTest, WhenCorrectPhone_ThenReturnsTrue) {
    std::string input(Constants::PHONE_LENGTH, '5');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::PHONE));
}

TEST(GivenValidatorPhoneTest, WhenBelowLength_ThenReturnsFalse) {
    std::string input(Constants::PHONE_LENGTH - 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PHONE));
}

TEST(GivenValidatorPhoneTest, WhenAboveLength_ThenReturnsFalse) {
    std::string input(Constants::PHONE_LENGTH + 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PHONE));
}

// Pin Tests

TEST(GivenValidatorPinTest, WhenCorrectPin_ThenReturnsTrue) {
    std::string input(Constants::PIN_LENGTH, '5');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::PIN));
}

TEST(GivenValidatorPinTest, WhenBelowLength_ThenReturnsFalse) {
    std::string input(Constants::PIN_LENGTH - 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PIN));
}

TEST(GivenValidatorPinTest, WhenAboveLength_ThenReturnsFalse) {
    std::string input(Constants::PIN_LENGTH + 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PIN));
}

// Account Number Tests

TEST(GivenValidatorAccountNumberTest, WhenCorrectAccountNumber_ThenReturnsTrue) {
    std::string input(Constants::ACCOUNT_NUMBER_LENGTH, '5');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::ACCOUNT_NUMBER));
}

TEST(GivenValidatorAccountNumberTest, WhenBelowLength_ThenReturnsFalse) {
    std::string input(Constants::ACCOUNT_NUMBER_LENGTH - 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::ACCOUNT_NUMBER));
}

TEST(GivenValidatorAccountNumberTest, WhenAboveLength_ThenReturnsFalse) {
    std::string input(Constants::ACCOUNT_NUMBER_LENGTH + 1, '5');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::ACCOUNT_NUMBER));
}

TEST_P(GivenValidatorInvalidCharTest, WhenPhoneContainsInvalidChar_ThenReturnsFalse) {
    std::string input(Constants::PHONE_LENGTH, '5');
    input[Constants::PHONE_LENGTH - 1] = GetParam();
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PHONE));
}

TEST_P(GivenValidatorInvalidCharTest, WhenPinContainsInvalidChar_ThenReturnsFalse) {
    std::string input(Constants::PIN_LENGTH, '5');
    input[Constants::PIN_LENGTH - 1] = GetParam();
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PIN));
}

TEST_P(GivenValidatorInvalidCharTest, WhenAccountNumberContainsInvalidChar_ThenReturnsFalse) {
    std::string input(Constants::ACCOUNT_NUMBER_LENGTH, '5');
    input[Constants::ACCOUNT_NUMBER_LENGTH - 1] = GetParam();
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::ACCOUNT_NUMBER));
}

INSTANTIATE_TEST_SUITE_P(InvalidChars, GivenValidatorInvalidCharTest,
    ::testing::Values('A', '@', 'b')
);

// Password Tests

TEST(GivenValidatorPasswordTest, WhenExactMinLengthAllAlpha_ThenReturnsTrue) {
    std::string input(Constants::MIN_PASSWORD_LENGTH, 'x');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::PASSWORD));
}

TEST(GivenValidatorPasswordTest, WhenContainsDigit_ThenReturnsTrue) {
    std::string input(Constants::MIN_PASSWORD_LENGTH + 1, 'x');
    input[Constants::MIN_PASSWORD_LENGTH - 1] = '1';
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::PASSWORD));
}

TEST(GivenValidatorPasswordTest, WhenContainsSpecialChar_ThenReturnsTrue) {
    std::string input(Constants::MIN_PASSWORD_LENGTH + 1, 'A');
    input[Constants::MIN_PASSWORD_LENGTH - 1] = '@';
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::PASSWORD));
}

TEST(GivenValidatorPasswordTest, WhenBelowMinLength_ThenReturnsFalse) {
    std::string input(Constants::MIN_PASSWORD_LENGTH - 1, 'x');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::PASSWORD));
}

// Username Tests

TEST(GivenValidatorUsernameTest, WhenExactMinLengthAllAlpha_ThenReturnsTrue) {
    std::string input(Constants::MIN_USERNAME_LENGTH, 'x');
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::USERNAME));
}

TEST(GivenValidatorUsernameTest, WhenContainsDigit_ThenReturnsTrue) {
    std::string input(Constants::MIN_USERNAME_LENGTH + 1, 'x');
    input[Constants::MIN_USERNAME_LENGTH - 1] = '1';
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::USERNAME));
}

TEST(GivenValidatorUsernameTest, WhenContainsSpecialChar_ThenReturnsTrue) {
    std::string input(Constants::MIN_USERNAME_LENGTH + 1, 'A');
    input[Constants::MIN_USERNAME_LENGTH - 1] = '@';
    EXPECT_TRUE(Validator::isValidInput(input, Constants::InputType::USERNAME));
}

TEST(GivenValidatorUsernameTest, WhenBelowMinLength_ThenReturnsFalse) {
    std::string input(Constants::MIN_USERNAME_LENGTH - 1, 'x');
    EXPECT_FALSE(Validator::isValidInput(input, Constants::InputType::USERNAME));
}
