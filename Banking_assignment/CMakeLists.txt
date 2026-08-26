cmake_minimum_required(VERSION 3.16)
project(BankAppSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Compiler warnings ────────────────────────────────────────────────────────
add_compile_options(-Wall -Wextra -Wpedantic)

# ── Sources ───────────────────────────────────────────────────────────────────
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)

file(GLOB BANK_SOURCES ${SRC_DIR}/*.cpp)

# ── Shared library ────────────────────────────────────────────────────────────
add_library(banklib STATIC ${BANK_SOURCES})
target_include_directories(banklib PUBLIC ${INC_DIR})

# ── Main executable ───────────────────────────────────────────────────────────
add_executable(BankAppSimulator ${CMAKE_SOURCE_DIR}/main/main.cpp)
target_link_libraries(BankAppSimulator PRIVATE banklib)

# ── Tests ─────────────────────────────────────────────────────────────────────
enable_testing()

set(GTEST_INCLUDE /usr/src/googletest/googletest/include)
set(GMOCK_INCLUDE /usr/src/googletest/googlemock/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/Test)

if(EXISTS ${GTEST_INCLUDE} AND EXISTS ${GMOCK_INCLUDE})
    file(GLOB TEST_SOURCES ${TEST_DIR}/src/*.cpp)

    add_executable(BankTests
        ${TEST_SOURCES}
        ${TEST_DIR}/main/main.cpp
    )

    target_include_directories(BankTests PRIVATE
        ${INC_DIR}
        ${TEST_DIR}/inc
        ${GTEST_INCLUDE}
        ${GMOCK_INCLUDE}
    )

    target_link_libraries(BankTests PRIVATE
        banklib
        gtest gmock pthread
    )

    add_test(NAME BankTests COMMAND BankTests)
else()
    message(WARNING "Google Test not found at expected path — test target skipped.")
endif()
