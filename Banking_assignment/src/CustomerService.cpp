#include "CustomerService.h"
#include <random>
#include <string>

long CustomerService::accountNumberCounter = Constants::INITIAL_ACCOUNT_NUMBER;

std::string CustomerService::generateRandomPin() {
    // Static locals are initialised once on first call and shared across all
    // subsequent invocations. Keeping the engine and distribution as statics
    // avoids re-seeding on every PIN generation, which is both faster and
    // produces better statistical distribution.
    static std::random_device randomDevice;
    static std::mt19937 gen(randomDevice());
    static std::uniform_int_distribution<> distribution(Constants::MIN_PIN_VALUE, Constants::MAX_PIN_VALUE);

    return std::to_string(distribution(gen));
}

Customer* CustomerService::findCustomerByAccountNumber(const std::string& accountNumber) {
    for (auto& customer : customers)
    {
        if (customer.getAccount().getAccountNumber() == accountNumber)
        {
            return &customer;
        }
    }
    return nullptr;
}

RegistrationResult CustomerService::createCustomer(const std::string& name,
                                                   const std::string& email,
                                                   const std::string& phone) {
    Customer newCustomer(name, email, phone);

    std::string accountNumber = std::to_string(accountNumberCounter++);
    std::string pin = generateRandomPin();

    newCustomer.getAccount().setAccountNumber(accountNumber);
    newCustomer.getAccount().setPin(pin);

    customers.push_back(std::move(newCustomer));

    return {&customers.back(), accountNumber, pin};
}

bool CustomerService::deleteCustomerFromBank(const std::string& accountNumber) {
    for (auto it = customers.begin(); it != customers.end(); ++it)
    {
        if (it->getAccount().getAccountNumber() == accountNumber)
        {
            if (it->getAccount().getBalance() == 0)
            {
                customers.erase(it);
                return true;
            }
            break;
        }
    }
    return false;
}
