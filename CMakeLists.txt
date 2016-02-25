cmake_minimum_required(VERSION 3.3)
project(GearRake C CXX)

find_package(Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# googletest build config
set(INCLUDE_LIST ${INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/gtest/include ${PROJECT_SOURCE_DIR}/gmock/include)
#add_subdirectory(google)
add_subdirectory(gmock gtest)
set(EXTRA_LIBS ${EXTA_LIBS} ${CMAKE_THREAD_LIBS_INIT} gmock gtest)

# GearRake build config
set(INCLUDE_LIST ${INCLUDE_LIST}
        test libDummys drafts drafts/actions)
set(SOURCE_FILES
#        src/schwader0_2.cpp
#        src/input_output.cpp
#        src/logging.cpp
#        src/task_management.cpp
#        src/tasks.cpp
#        libDummys/Adafruit_MCP23017.cpp
        test/gtest_main.cpp
        drafts/MessageBroker.h
        drafts/constants.h
        drafts/actions/io/Input.cpp
        drafts/actions/io/Input.h
        drafts/interfaces.h
        drafts/Message.cpp
        drafts/Message.h
        drafts/actions/Timer.cpp
        drafts/actions/Timer.h
        drafts/constants_message.h
        drafts/actions/Move.cpp
        drafts/actions/Move.h
        drafts/actions/io/Led.cpp
        drafts/actions/io/Led.h
        drafts/ConfigStore.cpp
        drafts/ConfigStore.h
        drafts/actions/auto/FrameDown.cpp
        drafts/actions/auto/FrameDown.h
        test/mocks.h
        test/gtest_move.cpp
        test/gtest_frame_down.cpp
        test/mocks.cpp
        test/MessageGenerator.cpp
        test/MessageGenerator.h
        test/gtest_timer.cpp
        test/gtest_diagnose.cpp
        test/gtest_configstore.cpp
        drafts/actions/Master.cpp
        drafts/actions/Master.h
        drafts/actions/Diagnose.cpp
        drafts/actions/Diagnose.h
        drafts/SerialProtocol.cpp
        drafts/SerialProtocol.h
        test/gtest_serial_protocol.cpp
        drafts/MessageBroker.cpp
        drafts/constants_io.h
        drafts/actions/io/Output.cpp
        drafts/actions/io/Output.h
        drafts/actions/HealthChecker.cpp
        drafts/actions/HealthChecker.h
        drafts/actions/io/Position.cpp
        drafts/actions/io/Position.h
        drafts/wrapper.cpp
        drafts/wrapper.h
        drafts/main.cpp drafts/constants_io.cpp drafts/cylinders/FrameLock.cpp drafts/cylinders/FrameLock.h drafts/cylinders/SpinnerRight.cpp drafts/cylinders/SpinnerRight.h drafts/cylinders/SpinnerLeft.cpp drafts/cylinders/SpinnerLeft.h drafts/cylinders/SpinnerTeleLeft.cpp drafts/cylinders/SpinnerTeleLeft.h drafts/cylinders/SpinnerTeleRight.cpp drafts/cylinders/SpinnerTeleRight.h drafts/cylinders/Frame.cpp drafts/cylinders/Frame.h drafts/cylinders/WeelTeleRight.cpp drafts/cylinders/WeelTeleRight.h drafts/cylinders/WeelTeleLeft.cpp drafts/cylinders/WeelTeleLeft.h drafts/cylinders/WeelSteer.cpp drafts/cylinders/WeelSteer.h drafts/cylinders/SpinnerRight.cpp drafts/cylinders/SpinnerRight.h drafts/actions/auto/Transport.cpp drafts/actions/auto/Transport.h drafts/actions/auto/Work.cpp drafts/actions/auto/Work.h drafts/actions/auto/Low.cpp drafts/actions/auto/Low.h drafts/actions/io/Led.cpp drafts/actions/io/Led.h drafts/actions/io/FailureStorage.cpp drafts/actions/io/FailureStorage.h drafts/cylinders/SpinnerRear.cpp drafts/cylinders/SpinnerRear.h)
#FILE( GLOB_RECURSE SOURCE_FILES src/*.cpp test/*.cpp)


# actually do it
include_directories(${INCLUDE_LIST})
add_executable(GearRake ${SOURCE_FILES})
target_link_libraries(GearRake ${EXTRA_LIBS})

#add_executable(firstgtest ${SOURCE_FILES})
