# Banking Application Simulator

A console-based banking application written in **C++17**, demonstrating clean architecture, SOLID principles, smart-pointer memory management, and modern C++ idioms.

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Architecture](#architecture)
4. [Folder Structure](#folder-structure)
5. [Prerequisites](#prerequisites)
6. [Build Instructions](#build-instructions)
7. [Running the Application](#running-the-application)
8. [Running the Tests](#running-the-tests)
9. [Default Credentials](#default-credentials)
10. [Configuration](#configuration)
11. [Usage Guide](#usage-guide)

---

## Overview

The Banking Application Simulator models a simple bank with a single administrator and multiple registered customers.  The admin can create and manage customer accounts; customers can perform self-service transactions.  The program runs entirely in the terminal and has no external runtime dependencies.

---

## Features

### Admin operations
| # | Feature |
|---|---------|
| 1 | Register a new customer (auto-generates account number and 4-digit PIN) |
| 2 | View all customers |
| 3 | View all accounts with balances |
| 4 | Search a customer by account number |
| 5 | Search an account by account number |
| 6 | Edit customer details (name, email, phone, PIN) |
| 7 | Manage a customer's account (deposit, withdraw, check balance) |
| 8 | Delete a customer (only permitted when balance is zero) |

### Customer operations
| # | Feature |
|---|---------|
| 1 | Deposit funds |
| 2 | Withdraw funds |
| 3 | Check current balance |
| 4 | Change PIN (requires current PIN verification; forces re-login) |
| 5 | View mini statement (last 5 transactions) |
| 6 | View full bank statement |

---

## Architecture

The project follows a layered architecture with clear separation of concerns:

```
┌──────────────────────────────────────────────┐
│                BankingSystem                  │  Entry point / thin facade
├──────────────────────────────────────────────┤
│                   Bank                        │  Login orchestration, main loop
├─────────────────────┬────────────────────────┤
│  AdminLoginHandler  │  CustomerLoginHandler   │  Role-specific authentication
├─────────────────────┴────────────────────────┤
│   AdminController   │   CustomerController    │  Use-case orchestration
├─────────────────────┴────────────────────────┤
│              CustomerService                  │  Customer/account lifecycle
├──────────────────┬───────────────────────────┤
│  Customer/Account │  Admin                   │  Domain entities
├──────────────────┴───────────────────────────┤
│   Display   │   InputHandler   │  Validator   │  Infrastructure / utilities
└──────────────────────────────────────────────┘
```

**Key design decisions:**

- `IBank`, `ILoginHandler`, and `IUser` are abstract interfaces enabling mock injection in tests.
- `Bank` owns its subsystems via `std::unique_ptr` (controllers) and `std::shared_ptr` (handlers), eliminating all manual `new`/`delete`.
- `CustomerService` stores customers in `std::list` to guarantee pointer stability across insertions.
- `Validator` returns a `ValidationResult` struct instead of printing errors, keeping I/O out of the domain layer.
- `CustomerService::createCustomer()` returns a `RegistrationResult` struct, keeping display logic in the controller.

---

## Folder Structure

```
Banking_assignment/
├── CMakeLists.txt              # CMake build configuration
├── README.md
├── docs/
│   └── USAGE.md                # Application walkthrough with sample interactions
├── inc/                        # Public header files
│   ├── Account.h
│   ├── Admin.h
│   ├── AdminController.h
│   ├── AdminLoginHandler.h
│   ├── Bank.h
│   ├── BankingSystem.h
│   ├── Constants.h             # Numeric limits, character literals, enumerations
│   ├── Customer.h
│   ├── CustomerController.h
│   ├── CustomerLoginHandler.h
│   ├── CustomerService.h       # Includes RegistrationResult struct
│   ├── Display.h
│   ├── IBank.h
│   ├── ILoginHandler.h
│   ├── InputHandler.h
│   ├── IUser.h
│   ├── Messages.h              # All user-facing string literals
│   ├── Transaction.h
│   ├── User.h
│   └── Validator.h             # Includes ValidationResult struct
├── src/                        # Implementation files
│   ├── Account.cpp
│   ├── Admin.cpp
│   ├── AdminController.cpp
│   ├── AdminLoginHandler.cpp
│   ├── Bank.cpp
│   ├── Customer.cpp
│   ├── CustomerController.cpp
│   ├── CustomerLoginHandler.cpp
│   ├── CustomerService.cpp
│   ├── Display.cpp
│   ├── InputHandler.cpp
│   ├── Transaction.cpp
│   └── Validator.cpp
├── main/
│   └── main.cpp
└── Test/
    ├── inc/                    # Test fixture headers + mock objects
    ├── src/                    # Test source files (Google Test / Google Mock)
    └── main/
        └── main.cpp            # Google Test runner entry point
```

---

## Prerequisites

| Dependency | Minimum version | Notes |
|---|---|---|
| C++ compiler | GCC 11 / Clang 14 | C++17 required (`-std=c++17`) |
| CMake | 3.16 | For the CMake build path |
| libgtest-dev | 1.11 | Google Test / Google Mock for running tests |

**Install on Ubuntu / Debian:**
```bash
sudo apt update && sudo apt install build-essential cmake libgtest-dev
```

---

## Build Instructions

### Option A — CMake (recommended)

```bash
# Configure (Release build)
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build everything (application + tests)
cmake --build build

# The built binaries are:
#   build/BankAppSimulator   — main application
#   build/BankTests          — test runner
```

### Option B — g++ directly

```bash
# 1. Compile all source files into object files
mkdir -p bin
cd bin && g++ -std=c++17 -I../inc -fPIC -c ../src/*.cpp && cd ..

# 2. Create a shared library
g++ -shared -o libbank.so bin/*.o

# 3. Build and link the executable
g++ -std=c++17 -I./inc main/main.cpp -L. -lbank -Wl,-rpath=. -o BankAppSimulator.out
```

---

## Running the Application

```bash
# CMake build
./build/BankAppSimulator

# Direct g++ build
./BankAppSimulator.out
```

You will be presented with the main menu:

```
=============== WELCOME ===============
1. Login as an Admin
2. Login as a Customer
3. Exit
========================================
```

See [docs/USAGE.md](docs/USAGE.md) for a full walkthrough with sample interactions.

---

## Running the Tests

### Via CMake

```bash
cmake --build build --target BankTests
cd build && ctest --output-on-failure
```

### Via g++ directly

```bash
cd Test
g++ -std=c++17 -I../src -I../inc -I./inc \
    -I/usr/src/googletest/googletest/include \
    -I/usr/src/googletest/googlemock/include \
    ../src/*.cpp src/*.cpp main/main.cpp \
    -lgtest -lgmock -lpthread -o BankTests.out

./BankTests.out
```

**Test coverage summary:**

| Suite | Tests | What is covered |
|---|---|---|
| `GivenAccountTest` | 22 | Deposit, withdrawal, PIN, balance, transaction history, boundary values |
| `GivenValidatorNameTest` | 3 | Name length and character set rules |
| `GivenValidatorEmailTest` | 5 | Email structure rules |
| `GivenValidatorPhoneTest` | 3 | Phone length and digit-only rule |
| `GivenValidatorPinTest` | 3 | PIN length and digit-only rule |
| `GivenValidatorAccountNumberTest` | 3 | Account number length and digit-only rule |
| `GivenValidatorPasswordTest` | 4 | Password minimum length |
| `GivenValidatorUsernameTest` | 4 | Username minimum length |
| `GivenValidatorInvalidCharTest` | 9 | Invalid characters (parameterised) |
| `GivenValidationResultTest` | 2 | ValidationResult struct and operator bool() |
| `GivenTransactionTest` | 4 | Construction, ID counter, setPostBalance |
| `GivenCustomerTest` | 9 | Constructor, setters, authentication |
| `GivenCustomerServiceTest` | 14 | CRUD, account numbers, PIN format, RegistrationResult |
| `GivenAdminTest` | 5 | Construction, authentication, setName |
| `GivenBankTest` | 11 | Login retry, role dispatch, handleChoice |
| `GivenBankingSystemTest` | 1 | execute() delegates to Bank::handleMenu() |
| `GivenRemovesWhitespaceTest` | 12 | Whitespace trimming (spaces, tabs, newlines, mixed) |

### Test filtering examples

```bash
# Run a single named test
./BankTests.out --gtest_filter=GivenAccountTest.WhenDepositValidAmount_ThenBalanceIncreases

# Run all tests in a fixture
./BankTests.out --gtest_filter=GivenAccountTest.*

# Run all parameterised tests in a suite
./BankTests.out --gtest_filter=InvalidAmounts/*

# Run multiple suites
./BankTests.out --gtest_filter=GivenAccountTest.*:GivenValidatorNameTest.*

# Exclude a suite
./BankTests.out --gtest_filter=-GivenBankTest.*

# Exclude a single test
./BankTests.out --gtest_filter=-GivenAccountTest.WhenConstructorCalled_ThenBalanceInitializedToZero
```

---

## Default Credentials

The application ships with one hardcoded admin account:

| Field | Value |
|---|---------|
| Username | `hiya` |
| Password | `system` |

> **Security note:** Admin credentials are currently stored as plaintext constants in `inc/Constants.h`.  In a production system these should be stored as salted hashes and loaded from a secure configuration source at startup.

Customer account numbers and PINs are generated automatically when the admin registers a customer.  The account number is an 8-digit integer starting at `10000000` and incrementing by 1; the PIN is a randomly generated 4-digit number.

---

## Configuration

Application-wide limits and defaults are defined in `inc/Constants.h`.  Change these values to reconfigure the application without touching business logic:

| Constant | Default | Description |
|---|---|---|
| `MAX_LOGIN_ATTEMPTS` | `3` | Failed attempts before the session is locked |
| `MIN_TRANSACTION_AMOUNT` | `100` | Minimum single-transaction amount |
| `MAX_TRANSACTION_AMOUNT` | `10000` | Maximum single-transaction amount |
| `PIN_LENGTH` | `4` | Number of digits in an account PIN |
| `MIN_NAME_LENGTH` | `3` | Minimum characters in a customer name |
| `MIN_PASSWORD_LENGTH` | `6` | Minimum characters in the admin password |
| `MINI_STATEMENT_MAX_TRANSACTIONS` | `5` | Transactions shown in a mini statement |
| `INITIAL_ACCOUNT_NUMBER` | `10000000` | Starting value for account number generation |

---

## Usage Guide

See **[docs/USAGE.md](docs/USAGE.md)** for step-by-step walkthroughs of every application flow with annotated sample terminal sessions.


## Steps to Run the Program

1. **Create a `bin` directory to store object files:**

```bash
mkdir bin
```

2. **Compile the source files into position-independent code (`.o` files):**

```bash
cd bin && g++ -I../inc -fPIC -c ../src/*.cpp && cd ..
```

3. **Create the shared library:**

```bash
g++ -shared -o libbank.so bin/*.o
```

4. **Compile the main program and link it with the shared library:**

```bash
g++ -I./inc main/main.cpp -L. -lbank -Wl,-rpath=. -o BankAppSimulator.out
```

5. **Run the program:**

```bash
./BankAppSimulator.out
```

---

## Steps to Run the Tests

### Compile all tests in single test file

```bash
cd Test && g++ -I../src -I../inc -I./inc ../src/*.cpp src/*.cpp main/main.cpp -lgtest -lgmock -lpthread -o BankTests.out

### Compile a single test file

```bash
cd Test && g++ -I../src -I../inc -I./inc ../src/*.cpp src/ValidatorTest.cpp main/main.cpp -lgtest -lgmock -lpthread -o BankTests.out
```

Replace `ValidatorTest.cpp` with any other test file to compile that file instead.

### Run the tests

```bash
./BankTests.out
```

---

### Filtering Tests

**Run a single test:**
```bash
./BankTests.out --gtest_filter=ValidatorNameTest.ExactMinLength_AllAlpha_ReturnsTrue
```

**Run all tests in a fixture or suite:**
```bash
./BankTests.out --gtest_filter=ValidatorNameTest.*
```

**Run all parameterized tests:**
```bash
./BankTests.out --gtest_filter=InvalidChars/*
```

**Run a specific parameterized fixture:**
```bash
./BankTests.out --gtest_filter=InvalidChars/ValidatorDigitsInvalidCharTest.*
```

**Run multiple suites:**
```bash
./BankTests.out --gtest_filter=ValidatorNameTest.*:ValidatorEmailTest.*
```

---

### Excluding Tests

**Skip a suite:**
```bash
./BankTests.out --gtest_filter=-ValidatorNameTest.*
```

**Skip a single test:**
```bash
./BankTests.out --gtest_filter=-ValidatorNameTest.ExactMinLength_AllAlpha_ReturnsTrue
```

**Skip multiple suites:**
```bash
./BankTests.out --gtest_filter=-ValidatorNameTest.*:-ValidatorEmailTest.*
```

---

### Disabling Tests

Prefix the test name with `DISABLED_` to disable it without deleting it:

```cpp
TEST(ValidatorNameTest, DISABLED_ExactMinLength_AllAlpha_ReturnsTrue) {
    ...
}
```

To explicitly run disabled tests:
```bash
./BankTests.out --gtest_filter=*DISABLED_*
```

---

### Other Useful Commands

**List all tests without running them:**
```bash
./BankTests.out --gtest_list_tests
```

**Repeat tests multiple times** (useful for catching flaky tests):
```bash
./BankTests.out --gtest_repeat=3 --gtest_filter=ValidatorNameTest.*
```
