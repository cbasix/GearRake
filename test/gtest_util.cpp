#include <util.h>
#include <gtest/gtest.h>
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


//
// Created by cyberxix on 26.02.16.
//
/*
TEST(Util, Complete){
    int data[20];
    ArrayList<int>* al = new ArrayList<int>(data, 20);
    for (int i = 0; i < 25; ++i) {
        al->append(i);
    }

    int t = 0;
    while(al->getSize() > 0){
        int ret = al->get(0);
        al->remove(0);

        ASSERT_EQ(t, ret);
        t++;
    }
    ASSERT_EQ(19, t);



}
*/