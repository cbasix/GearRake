//
// Created by cyberxix on 24.02.16.
//

#include <actions/Master.h>
#include <cylinders/Frame.h>
#include <cylinders/FrameLock.h>
#include <cylinders/SpinnerLeft.h>
#include <cylinders/SpinnerRight.h>
#include <cylinders/SpinnerTeleLeft.h>
#include <cylinders/WeelTeleLeft.h>
#include <cylinders/SpinnerTeleRight.h>
#include <cylinders/WeelTeleRight.h>
#include <cylinders/WeelSteer.h>
#include <actions/io/Position.h>
#include <actions/io/Output.h>
#include <actions/io/Input.h>
#include <cylinders/SpinnerRear.h>
#include "MessageBroker.h"

void setup(MessageBroker* mb) {

    //Setup expanders
    ExpanderWrapper exp[EXP_LEN];
    exp[0] = ExpanderWrapper(EXP1_ADDR);
    exp[1] = ExpanderWrapper(EXP2_ADDR);
    exp[2] = ExpanderWrapper(EXP3_ADDR);

    //Setup Input lists.
    InputData manual_inputs[(int)ManualInputId::ENUM_COUNT];
    for (int i = 0; i < (int)ManualInputId::ENUM_COUNT; ++i) {
        manual_inputs[i] = InputData(ManualInputPin::getPin((ManualInputId) i));
    }

    InputData sensor_inputs[(int)SensorInputId::ENUM_COUNT];
    for (int i = 0; i < (int)SensorInputId::ENUM_COUNT; ++i) {
        sensor_inputs[i] = InputData(SensorInputPin::getPin((SensorInputId) i));
    }


    //Setup output list. cylinder outputs and leds
    OutputData outputs[(int)OutputId::ENUM_COUNT];
    for (int i = 0; i < (int)OutputId::ENUM_COUNT; ++i) {
        outputs[i] = OutputData(OutputPin::getPin((OutputId) i));
    }

    //Setup cylinders
    Cylinder* cylinders[(int)CylinderId::ENUM_COUNT];
    cylinders[(int)CylinderId::FRAME] = new Frame;
    cylinders[(int)CylinderId::FRAME_LOCK] = new FrameLock;
    cylinders[(int)CylinderId::SPINNER_LEFT] = new SpinnerLeft;
    cylinders[(int)CylinderId::SPINNER_RIGHT] = new SpinnerRight;
    cylinders[(int)CylinderId::SPINNER_TELE_LEFT] = new SpinnerTeleLeft;
    cylinders[(int)CylinderId::SPINNER_TELE_RIGHT] = new SpinnerTeleRight;
    cylinders[(int)CylinderId::WEEL_TELE_LEFT] = new WeelTeleLeft;
    cylinders[(int)CylinderId::WEEL_TELE_RIGHT] = new WeelTeleRight;
    cylinders[(int)CylinderId::WEEL_STEER] = new WeelSteer;
    cylinders[(int)CylinderId::SPINNER_REAR] = new SpinnerRear;


    //todo test is that all we need?
    //setup io-tasks and master task which starts all other needed tasks
    mb->registerProducer((Producer *) new Input(manual_inputs, (int)ManualInputId::ENUM_COUNT)); //one input task for whe manual inputs
    mb->registerProducer((Producer *) new Input(sensor_inputs, (int)SensorInputId::ENUM_COUNT)); //and a second one for the sensor inputs
    mb->registerConsumer((Consumer *) new Output(exp, EXP_LEN, outputs, (int)OutputId::ENUM_COUNT, cylinders, (int)CylinderId::ENUM_COUNT));
    mb->registerConsumer((Consumer *) new Position(cylinders, (int)CylinderId::ENUM_COUNT));
    mb->registerConsumer((Consumer *) new Master(mb));

};

void loop(MessageBroker* mb){
    mb->runProducers();
    mb->processMessageQueue();
}

