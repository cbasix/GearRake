//
// Created by cyberxix on 18.02.16.
//
#include <ConfigStore.h>
#include <actions/auto/FrameDown.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "MessageGenerator.h"

using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;



class FrameDownTest : public ::testing::Test {
private:

public:
    EmptyController ec;
    MockController c;
    FrameDown* fd;
    int child_comm_id;
    int parent_comm_id;
    FrameDownTest(){
        parent_comm_id = Message::generateCommunicationId();
        child_comm_id = parent_comm_id+1;

        //ignore constructor calls we want to test something different
        this->fd = new FrameDown(&ec, parent_comm_id);
    }

    ~FrameDownTest() { delete fd; }
};

TEST_F(FrameDownTest, Constructor) {
    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message request_short_up(MessageType::MOVE_TIME_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    request_short_up.setValue(MessageField::MOVE_TIME_REQUEST__CYLINDER, (int) CylinderId::FRAME);
    request_short_up.setValue(MessageField::MOVE_TIME_REQUEST__DIRECTION, (int)CylinderDirection::UP);
    request_short_up.setValue(MessageField::MOVE_TIME_REQUEST__TIMING, (int)Timing::SHORT);

    EXPECT_CALL(c, queueMessage(request_short_up)).Times(1);

    //start move time should produce request_timer and request_start cylinder
    FrameDown fd(&c, parent_comm_id);
}

TEST_F(FrameDownTest, ShortFrameUp) {
    fd->setState(FrameDown::LocalState::SHORT_FRAME_UP);

    Message request_move_position(MessageType::MOVE_POSITION_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    request_move_position.setValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER, (int) CylinderId::FRAME_LOCK);
    request_move_position.setValue(MessageField::MOVE_POSITION_REQUEST__POSITION, (int) CylinderPosition::OPEN);

    //EXPECT_CALL(c, queueMessage(_)).Times(0);
    EXPECT_CALL(c, queueMessage(request_move_position)).Times(1);

    Message answer_short_up(MessageType::ACTION_STATE, ActionType::MOVE_TIME, child_comm_id);
    answer_short_up.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    fd->onMessage(&c, &answer_short_up);
    EXPECT_EQ(fd->getState(), FrameDown::LocalState::OPEN_LOCK);
}

TEST_F(FrameDownTest, ShortFrameUpRandom) {
    fd->setState(FrameDown::LocalState::SHORT_FRAME_UP);

    EXPECT_CALL(c, queueMessage(_)).Times(0);

    Message answer_short_up(MessageType::ACTION_STATE, ActionType::MOVE_TIME, child_comm_id);
    answer_short_up.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    MessageGenerator mg(&answer_short_up, child_comm_id, true, false, true);

    mg.generate(&c, fd);
}

TEST_F(FrameDownTest, OpenLockNormal) {
    fd->setState(FrameDown::LocalState::OPEN_LOCK);

    //request move frame down
    Message request_move_cylinder(MessageType::CYLINDER_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    request_move_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::FRAME);
    request_move_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::DOWN);

    //EXPECT_CALL(c, queueMessage(_)).Times(0);
    EXPECT_CALL(c, queueMessage(request_move_cylinder)).Times(1);

    //simulate subprocess move framelock open is ready
    Message sub_ready(MessageType::ACTION_STATE, ActionType::MOVE_POSITION, child_comm_id);
    sub_ready.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    fd->onMessage(&c, &sub_ready);
    EXPECT_EQ(FrameDown::LocalState::FRAME_DOWN, fd->getState());
}

TEST_F(FrameDownTest, OpenLockCancelAndTimeout) {
    //rclose framelock
    Message move_position(MessageType::MOVE_POSITION_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    move_position.setValue(MessageField::MOVE_POSITION_REQUEST__POSITION, (int) CylinderPosition::CLOSED);
    move_position.setValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER, (int) CylinderId::FRAME_LOCK);

    EXPECT_CALL(c, queueMessage(move_position)).Times(2);

    //simulate timout
    fd->setState(FrameDown::LocalState::OPEN_LOCK);
    Message timeout(MessageType::TIMEOUT, ActionType::TIMER, child_comm_id);
    fd->onMessage(&c, &timeout);
    EXPECT_EQ(FrameDown::LocalState::CLOSE_LOCK, fd->getState());

    //simulate stop message from parent
    fd->setState(FrameDown::LocalState::OPEN_LOCK);
    Message stop(MessageType::ACTION_STATE, ActionType::INPUT, parent_comm_id);
    stop.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPING);
    fd->onMessage(&c, &stop);
    EXPECT_EQ(FrameDown::LocalState::CLOSE_LOCK, fd->getState());
}

TEST_F(FrameDownTest, FrameDown) {
    //stop movement of frame
    Message stop_cylinder(MessageType::CYLINDER_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, (int)CylinderDirection::STOP);
    stop_cylinder.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, (int) CylinderId::FRAME);

    //start close lock
    Message move_position(MessageType::MOVE_POSITION_REQUEST, ActionType::FRAME_DOWN, child_comm_id);
    move_position.setValue(MessageField::MOVE_POSITION_REQUEST__POSITION, (int) CylinderPosition::CLOSED);
    move_position.setValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER, (int) CylinderId::FRAME_LOCK);


    EXPECT_CALL(c, queueMessage(stop_cylinder)).Times(2);
    EXPECT_CALL(c, queueMessage(move_position)).Times(2);

    //simulate timout
    fd->setState(FrameDown::LocalState::FRAME_DOWN);
    Message timeout(MessageType::TIMEOUT, ActionType::TIMER, child_comm_id);
    fd->onMessage(&c, &timeout);
    EXPECT_EQ(FrameDown::LocalState::CLOSE_LOCK, fd->getState());

    //simulate stop message from parent
    fd->setState(FrameDown::LocalState::FRAME_DOWN);
    Message stop(MessageType::ACTION_STATE, ActionType::INPUT, parent_comm_id);
    stop.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPING);
    fd->onMessage(&c, &stop);
    EXPECT_EQ(FrameDown::LocalState::CLOSE_LOCK, fd->getState());
}

TEST_F(FrameDownTest, CloseLock) {
    //send timeout to parent
    Message create_timeout(MessageType::TIMEOUT, ActionType::FRAME_DOWN, parent_comm_id);
    create_timeout.setValue(MessageField::TIMEOUT__STATE, (int)FrameDown::LocalState::CLOSE_LOCK);
    //start close lock
    Message send_ok(MessageType::ACTION_STATE, ActionType::FRAME_DOWN, parent_comm_id);
    send_ok.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);

    EXPECT_CALL(c, removeConsumer(_)).Times(3);
    EXPECT_CALL(c, queueMessage(create_timeout)).Times(2);
    EXPECT_CALL(c, queueMessage(send_ok)).Times(1);

    //simulate timout
    fd->setState(FrameDown::LocalState::CLOSE_LOCK);
    Message timeout(MessageType::TIMEOUT, ActionType::TIMER, child_comm_id);
    fd->onMessage(&c, &timeout);
    //EXPECT_EQ(FrameDown::LocalState::CLOSE_LOCK, fd->getState());

    //simulate framelock close okay
    fd->setState(FrameDown::LocalState::CLOSE_LOCK);
    Message sub_ok(MessageType::ACTION_STATE, ActionType::MOVE_POSITION, child_comm_id);
    sub_ok.setValue(MessageField::ACTION_STATE__STATE, (int)ActionState::STOPPED_OK);
    fd->onMessage(&c, &sub_ok);

    //simulate framelock close okay but with previous timeout - reuse message from above
    fd->setState(FrameDown::LocalState::CLOSE_LOCK);
    fd->setTimeoutOccured(true);
    fd->onMessage(&c, &sub_ok);

}



