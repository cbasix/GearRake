// gtest_main.cpp
#include <stdio.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"


int main(int argc, char** argv) {
//    printf("Running main() from gtest_main.cc\n");

    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
