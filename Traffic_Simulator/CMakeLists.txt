cmake_minimum_required(VERSION 3.14)
project(TrafficLightSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/InputHandler.cpp
    src/Logger.cpp
    src/MoveResult.cpp
    src/TrafficController.cpp
    src/TrafficLightSystem.cpp
    src/TrafficLightSystemFactory.cpp
    src/UserController.cpp
    src/Utils.cpp
)

add_executable(TrafficLightSimulation
    main/main.cpp
    ${SOURCES}
)

target_include_directories(TrafficLightSimulation PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
)

target_link_libraries(TrafficLightSimulation
    pthread
)

find_package(GTest REQUIRED)
enable_testing()

set(TEST_SOURCES
    Test/src/UtilsTest.cpp
    Test/src/UserControllerTest.cpp
    Test/src/TrafficControllerTest.cpp
    Test/src/TrafficLightSystemTest.cpp
)

add_executable(TrafficLightSimulationTests
    ${TEST_SOURCES}
    ${SOURCES}
)

target_include_directories(TrafficLightSimulationTests PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/Test/inc
)

target_link_libraries(TrafficLightSimulationTests
    GTest::GTest
    GTest::Main
    GTest::gmock
    pthread
)

add_test(NAME TrafficLightSimulationTests COMMAND TrafficLightSimulationTests)
