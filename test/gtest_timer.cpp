//
// Created by cyberxix on 19.02.16.
//
//todo fix imports
#include <ConfigStore.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "actions/auto/FrameDown.h"
#include "MessageGenerator.h"
#include "Timer.h"

using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::InSequence;



/*class TimerTest : public ::testing::Test {
private:

public:
    EmptyController ec;
    MockController c;
    Timer* t;
    int child_comm_id;
    int parent_comm_id;
    TimerTest(){
        parent_comm_id = Message::generateCommunicationId();
        child_comm_id = parent_comm_id+1;
        Timing timer = TIMING::SHORT;//ConfigStore::getTimerValue(Timing::SHORT);
        bool is_timeout = true;

        //ignore constructor calls we want to test something different
        this->t = new Timer(parent_comm_id, timer, is_timeout);
    }
    ~TimerTest() {
        delete t;
    }
};*/


TEST(TimerTest, Complete){
    InSequence s;

    MockController c;
    int parent_comm_id = Message::generateCommunicationId();
    int child_comm_id = parent_comm_id+1;

    Message timeout(MessageType::TIMEOUT, ActionType::TIMER, parent_comm_id);
    timeout.setValue(MessageField::TIMEOUT__STATE, 0);

    Message timer(MessageType::TIMER_STATE, ActionType::TIMER, parent_comm_id);

    EXPECT_CALL(c, queueMessage(timeout)).Times(1);
    EXPECT_CALL(c, removeProducer(_)).Times(1);
    EXPECT_CALL(c, queueMessage(timer)).Times(1);
    EXPECT_CALL(c, removeProducer(_)).Times(1);


    //request timeout
    ClockWrapper::setReturnValue(1000);
    ConfigStore::setTimer(Timing::HUNDRED, 100);
    Timer lt(parent_comm_id, Timing::HUNDRED, true);

    //should not produce anything (timer not over)
    ClockWrapper::setReturnValue(1080);
    lt.produce(&c);

    //should produce timeout
    ClockWrapper::setReturnValue(1120);
    lt.produce(&c);

    //request timer
    ClockWrapper::setReturnValue(1000);
    Timer lt2(parent_comm_id, Timing::HUNDRED, false);

    //should not produce anything (timer not over)
    ClockWrapper::setReturnValue(1080);
    lt2.produce(&c);

    //should produce timer state
    ClockWrapper::setReturnValue(1120);
    lt2.produce(&c);
}