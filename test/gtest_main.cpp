// gtest_main.cpp
#include <stdio.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "Move.h"

using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

TEST(MoveTime, Normal) {
    MockController c;

    Message start_timer(MessageType::TIMER_REQUEST, ActionType::MOVE_TIME, 1);
    start_timer.setValue(MessageField::TIMER_REQUEST__STOP_AFTER, (int)100);

    Message start_in(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, 1);
    start_in.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int)Cylinder::SPINNER_RIGHT);
    start_in.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::UP);

    EXPECT_CALL(c, queueMessage(start_timer)).Times(1);
    EXPECT_CALL(c, queueMessage(start_in)).Times(1); //.WillRepeatedly(Return(200))

    MoveTime mt(&c, 99, Cylinder::SPINNER_RIGHT, CylinderDirection::UP, 100);


    /*mt.onMessage(&c, m);
    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
    EXPECT_EQ(1, 1);*/
}

int main(int argc, char** argv) {
    printf("Running main() from gtest_main.cc\n");

    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
