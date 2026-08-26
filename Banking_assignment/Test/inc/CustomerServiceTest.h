#ifndef CUSTOMER_SERVICE_TEST_H
#define CUSTOMER_SERVICE_TEST_H

#include "CustomerService.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class GivenCustomerServiceTest : public ::testing::Test {
protected:
    CustomerService service;
    Customer* customer;

    void SetUp() override {
        auto result = service.createCustomer("Daksh Sharma", "daksh@gmail.com", "1234567890");
        customer = result.customer;
    }
};

#endif
