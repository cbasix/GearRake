//
// Created by cyberxix on 22.02.16.
//

#include <ConfigStore.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "FrameDown.h"
#include "MessageGenerator.h"
#include "Timer.h"
#include "SerialProtocol.h"

using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::InSequence;
using ::testing::ElementsAreArray;
using ::testing::ContainerEq;

#define TEST_MSG_BIN_LEN 12

/*class SerialProto : public ::testing::Test {
private:

public:
    SerialProtocol sp;
    SerialProto(){

    }
    ~SerialProto() {
    }
};*/


TEST(SerialProto, Serialize){
    char should[] = {0, 0x09, 0, 0x08, 0, 0x05, 0, 0, 0, 0, 0, 0};
    char bin_msg[TEST_MSG_BIN_LEN];
    Message m = Message(MessageType::TIMER_STATE, ActionType::TIMER, 5);
    SerialProtocol::serialize(&m, bin_msg, TEST_MSG_BIN_LEN);

    ASSERT_THAT(bin_msg, ContainerEq(should));


}

TEST(SerialProto, Deserialize){
    char bin_msg[] = {0, 0x09, 0, 0x08, 0, 0x05, 0, 0, 0, 0, 0, 0};
    Message should = Message(MessageType::TIMER_STATE, ActionType::TIMER, 5);
    Message m;

    SerialProtocol::deserialize(bin_msg, TEST_MSG_BIN_LEN, &m);

    GTEST_ASSERT_EQ(true, m == should);
}

TEST(SerialProto, Packetize){
    char checksum = 236;
    char bin_packet_should[] = {SerialChar::START, checksum, 0, 0x09, 0, 0x08, 0,  0x1b, 0x02, 0, 0, 0, 0, 0, 0, SerialChar::END};
    char bin_msg[] = {0, 0x09, 0, 0x08, 0, 0x02, 0, 0, 0, 0, 0, 0};

    CircularQueue<char> q = CircularQueue<char>((int)SerialConf::BUF_SIZE);


    SerialProtocol::packetize(bin_msg, TEST_MSG_BIN_LEN, &q);

    char bin_packet[sizeof(bin_packet_should)];
    for (int i = 0; i < sizeof(bin_packet_should); ++i) {
        bin_packet[i] = q.get();
    }
    GTEST_ASSERT_EQ(true, q.size() == 0);

    ASSERT_THAT(bin_packet_should, ContainerEq(bin_packet));
}

TEST(SerialProto, Depacketize){
    char wrong_checksum = 76;
    char checksum = 236;
    char bin_packet[] = {SerialChar::START, wrong_checksum, 0, 0x09, 0, 0x08, 0, 0x02, 0, 0, 0, 0, 0, 0, SerialChar::END};

    CircularQueue<char> q = CircularQueue<char>((int)SerialConf::BUF_SIZE);
    char bin_msg[TEST_MSG_BIN_LEN];

    for (int i = 0; i < sizeof(bin_packet); ++i) {
        q.add(bin_packet[i]);
    }

    //test packet with wrong checksum -> should be dropped silently and return false
    bool ret = SerialProtocol::depacketize(&q, bin_msg, TEST_MSG_BIN_LEN);

    GTEST_ASSERT_EQ(false, ret);
    GTEST_ASSERT_EQ(true, q.size() == 0);

    //test recive of sane package
    char bin_packet2[] = {SerialChar::START, checksum, 0, 0x09, 0, 0x08, 0, 0x1b, 0x02, 0, 0, 0, 0, 0, 0, SerialChar::END};
    for (int i = 0; i < sizeof(bin_packet2); ++i) {
        q.add(bin_packet2[i]);
    }
    char bin_msg_should[] = {0, 0x09, 0, 0x08, 0, 0x02, 0, 0, 0, 0, 0, 0};

    ret = SerialProtocol::depacketize(&q, bin_msg, TEST_MSG_BIN_LEN);

    GTEST_ASSERT_EQ(true, ret);
    GTEST_ASSERT_EQ(true, q.size() == 0);
    ASSERT_THAT(bin_msg_should, ContainerEq(bin_msg));
}