#ifndef CUSTOMER_TEST_H
#define CUSTOMER_TEST_H

#include "Customer.h"
#include <gtest/gtest.h>

class GivenCustomerTest : public ::testing::Test {
protected:
    Customer customer{"Daksh Sharma", "daksh@gmail.com", "6789543210"};

    void SetUp() {
        std::string accountNumber = "12345678";
        customer.getAccount().setAccountNumber(accountNumber);
        customer.getAccount().setPin("4321");
    }
};

#endif
