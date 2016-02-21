//
// Created by cyberxix on 19.02.16.
//

#include <ConfigStore.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mocks.h"
#include "FrameDown.h"
#include "MessageGenerator.h"

using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;



TEST(ConfigStoreTest, Complete) {
    ConfigStore::setTimer(Timing::SHORT, 1478);
    EXPECT_EQ(1478, ConfigStore::getTimerValue(Timing::SHORT));

    ConfigStore::setTimeout(CylinderPosition::MIDDLE , 111);
    EXPECT_EQ(111, ConfigStore::getTimeoutValue(CylinderPosition::MIDDLE));

}
