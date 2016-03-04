//
// Created by cyberxix on 18.02.16.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "Move.h"
#include "ConfigStore.h"



using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;

TEST(MoveTimeTest, Setup) {
    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message request_timer(MessageType::TIMER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_timer.setValue(MessageField::TIMER_REQUEST__TIMING, (int)Timing::SHORT);

    Message request_start_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::UP);

    Message request_stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::STOP);

    Message action_state(MessageType::ACTION_STATE, ActionType::MOVE_TIME, child_comm_id);
    action_state.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    EXPECT_CALL(c, queueMessage(request_timer)).Times(1);
    EXPECT_CALL(c, queueMessage(request_start_cylinder)).Times(1);


    //start move time should produce request_timer and request_start cylinder
    MoveTime mt(&c, parent_comm_id, CylinderId::SPINNER_RIGHT, CylinderDirection::UP, Timing::SHORT);

}

TEST(MoveTimeTest, StopRequest) {
    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message request_timer(MessageType::TIMER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_timer.setValue(MessageField::TIMER_REQUEST__TIMING, (int)Timing::SHORT);

    Message request_start_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::UP);

    Message request_stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::STOP);

    Message action_state(MessageType::ACTION_STATE, ActionType::MOVE_TIME, parent_comm_id);
    action_state.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    EXPECT_CALL(c, queueMessage(request_timer)).Times(1);
    EXPECT_CALL(c, queueMessage(request_stop_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(request_start_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(action_state)).Times(1);
    EXPECT_CALL(c, removeConsumer(_)).Times(1);

    //start move time should produce request_timer and request_start cylinder
    MoveTime mt(&c, parent_comm_id, CylinderId::SPINNER_RIGHT, CylinderDirection::UP, Timing::SHORT);

    //send timer status should produce request_stop_cylinder
    Message parent_stop(MessageType::ACTION_STATE, ActionType::INPUT, parent_comm_id);
    parent_stop.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPING);

    mt.onMessage(&c, &parent_stop);


    /*mt.onMessage(&c, m);
    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
    EXPECT_EQ(1, 1);*/
}

TEST(MoveTimeTest, TimeStop) {
    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message request_timer(MessageType::TIMER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_timer.setValue(MessageField::TIMER_REQUEST__TIMING, (int)Timing::SHORT);

    Message request_start_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::UP);

    Message request_stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_TIME, child_comm_id);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::STOP);

    Message action_state(MessageType::ACTION_STATE, ActionType::MOVE_TIME, parent_comm_id);
    action_state.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    EXPECT_CALL(c, queueMessage(request_timer)).Times(1);
    EXPECT_CALL(c, queueMessage(request_stop_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(request_start_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(action_state)).Times(1);
    EXPECT_CALL(c, removeConsumer(_)).Times(1);

    //start move time should produce request_timer and request_start cylinder
    MoveTime mt(&c, parent_comm_id, CylinderId::SPINNER_RIGHT, CylinderDirection::UP, Timing::SHORT);

    //send timer status should produce request_stop_cylinder
    Message timer_status(MessageType::TIMER_STATE, ActionType::TIMER, child_comm_id);

    mt.onMessage(&c, &timer_status);

    /*mt.onMessage(&c, m);
    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
    EXPECT_EQ(1, 1);*/
}

TEST(MoveDirectionTest, StopRequest) {
    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message request_start_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_DIRECTION, child_comm_id);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::UP);

    Message request_stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_DIRECTION, child_comm_id);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::SPINNER_RIGHT);
    request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::STOP);

    Message action_state(MessageType::ACTION_STATE, ActionType::MOVE_DIRECTION, parent_comm_id);
    action_state.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    EXPECT_CALL(c, queueMessage(request_stop_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(request_start_cylinder)).Times(1);
    EXPECT_CALL(c, queueMessage(action_state)).Times(1);
    EXPECT_CALL(c, removeConsumer(_)).Times(1);

    //start move time should produce request_timer and request_start cylinder
    MoveDirection mt(&c, parent_comm_id, CylinderId::SPINNER_RIGHT, CylinderDirection::UP, false);

    //send timer status should produce request_stop_cylinder
    Message parent_stop(MessageType::ACTION_STATE, ActionType::INPUT, parent_comm_id);
    parent_stop.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPING);

    mt.onMessage(&c, &parent_stop);


    /*mt.onMessage(&c, m);
    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
    EXPECT_EQ(1, 1);*/
}

TEST(MovePositionTest, Timeout) {
    //enum testno {TIMEOUT_FIRST, TIMEOUT, PARENT_STOP, TEST_COUNT};
    //for(int testno = 0; testno < TEST_COUNT; testno++) {
        MockController c;
        int parent_comm_id = Message::generateCommunicationId();
        int child_comm_id = parent_comm_id + 1;

        Message request_timeout(MessageType::TIMEOUT_REQUEST, ActionType::MOVE_POSITION, child_comm_id);
        request_timeout.setValue(MessageField::TIMEOUT_REQUEST__TIMEOUT,
                                 ConfigStore::getTimeoutValue(CylinderPosition::GROUND)); //timeout is defined in config_store

        Message request_start_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_POSITION, child_comm_id);
        request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::FRAME);
        request_start_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int) CylinderDirection::UP);

        Message request_stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::MOVE_POSITION, child_comm_id);
        request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::FRAME);
        request_stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int) CylinderDirection::STOP);

        Message position_request(MessageType::POSITION_REQUEST, ActionType::MOVE_POSITION, child_comm_id);
        position_request.setValue(MessageField::POSITION_REQUEST__CYLINDER, (int) CylinderId::FRAME);

        Message timeout(MessageType::TIMEOUT, ActionType::MOVE_POSITION, parent_comm_id);

        EXPECT_CALL(c, queueMessage(request_timeout)).Times(1);
        EXPECT_CALL(c, queueMessage(position_request)).Times(1);
        EXPECT_CALL(c, queueMessage(request_start_cylinder)).Times(1);

        EXPECT_CALL(c, queueMessage(request_stop_cylinder)).Times(1);

        EXPECT_CALL(c, queueMessage(timeout)).Times(1);
        EXPECT_CALL(c, removeConsumer(_)).Times(1);

        //start move time should produce request_timeout and a position_request
        MovePosition mt(&c, parent_comm_id, CylinderId::FRAME, CylinderPosition::MIDDLE);

        //the position answer should produce request_start cylinder
        Message position_state(MessageType::POSITION_STATE, ActionType::INPUT, child_comm_id);
        position_state.setValue(MessageField::POSITION_STATE__CYLINDER, (int) CylinderId::FRAME);
        position_state.setValue(MessageField::POSITION_STATE__POSITION, (int) CylinderPosition::GROUND);
        mt.onMessage(&c, &position_state);

        //the timout should produce a stop_cylinder and an timeout_message for the parent
        Message timeout_orig(MessageType::TIMEOUT, ActionType::TIMER, child_comm_id);
        mt.onMessage(&c, &timeout_orig);

    //}

    /*mt.onMessage(&c, m);
    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
    EXPECT_EQ(1, 1);*/
}