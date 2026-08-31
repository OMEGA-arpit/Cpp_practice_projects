#ifndef VALIDATOR_TEST_H
#define VALIDATOR_TEST_H

#include "Validator.h"
#include "Constants.h"
#include <gtest/gtest.h>

class GivenValidatorNameInvalidCharTest : public ::testing::TestWithParam<char> {};

class GivenValidatorEmailInvalidFormatTest : public ::testing::TestWithParam<std::string> {};

class GivenValidatorInvalidCharTest : public ::testing::TestWithParam<char> {};

#endif
