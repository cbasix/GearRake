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
        src test libDummys drafts drafts/actions)
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
        drafts/actions/Input.cpp
        drafts/actions/Input.h
        drafts/interfaces.h
        drafts/Message.cpp
        drafts/Message.h
        drafts/actions/Timer.cpp
        drafts/actions/Timer.h
        drafts/constants_message.h
        drafts/actions/Move.cpp
        drafts/actions/Move.h
        drafts/actions/Led.cpp
        drafts/actions/Led.h
        drafts/ConfigStore.cpp
        drafts/ConfigStore.h
        drafts/actions/FrameDown.cpp
        drafts/actions/FrameDown.h
        test/mocks.h
        test/gtest_move.cpp
        test/gtest_frame_down.cpp
        test/mocks.cpp
        test/MessageGenerator.cpp
        test/MessageGenerator.h
        test/gtest_timer.cpp
        test/gtest_diagnose.cpp
        test/gtest_configstore.cpp drafts/actions/Master.cpp drafts/actions/Master.h drafts/actions/Diagnose.cpp drafts/actions/Diagnose.h drafts/SerialProtocol.cpp drafts/SerialProtocol.h test/gtest_serial_protocol.cpp drafts/MessageBroker.cpp)
#FILE( GLOB_RECURSE SOURCE_FILES src/*.cpp test/*.cpp)


# actually do it
include_directories(${INCLUDE_LIST})
add_executable(GearRake ${SOURCE_FILES})
target_link_libraries(GearRake ${EXTRA_LIBS})

#add_executable(firstgtest ${SOURCE_FILES})
