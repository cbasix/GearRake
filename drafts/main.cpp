//
// Created by cyberxix on 26.02.16.
//

#include <actions/starter/Master.h>
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
#include <actions/Move.h>
#include "MessageBroker.h"

int main(){
    MessageBroker mb;

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
    Frame f = Frame();
    cylinders[(int)CylinderId::FRAME] = &f;
    FrameLock fl = FrameLock();
    cylinders[(int)CylinderId::FRAME_LOCK] = &fl;
    SpinnerLeft sl = SpinnerLeft();
    cylinders[(int)CylinderId::SPINNER_LEFT] = &sl;
    SpinnerRight sr = SpinnerRight();
    cylinders[(int)CylinderId::SPINNER_RIGHT] = &sr;
    SpinnerTeleLeft stl = SpinnerTeleLeft();
    cylinders[(int)CylinderId::SPINNER_TELE_LEFT] = &stl;
    SpinnerTeleRight str = SpinnerTeleRight();
    cylinders[(int)CylinderId::SPINNER_TELE_RIGHT] = &str;
    WeelTeleLeft wtl = WeelTeleLeft();
    cylinders[(int)CylinderId::WEEL_TELE_LEFT] = &wtl;
    WeelTeleRight wtr = WeelTeleRight();
    cylinders[(int)CylinderId::WEEL_TELE_RIGHT] = &wtr;
    WeelSteer ws = WeelSteer();
    cylinders[(int)CylinderId::WEEL_STEER] = &ws;
    SpinnerRear srea = SpinnerRear();
    cylinders[(int)CylinderId::SPINNER_REAR] = &srea;




    //todo test is that all we need?
    //setup io-tasks and master task which starts all other needed tasks
    Input i = Input(manual_inputs, (int)ManualInputId::ENUM_COUNT);
    Producer * pnt = &i;
    ActionType t = pnt->getType();
    mb.registerProducer(&i); //one input task for whe manual inputs
    Input i2 = Input(sensor_inputs, (int)SensorInputId::ENUM_COUNT);
    mb.registerProducer(&i2); //and a second one for the sensor inputs
    Output o = Output(exp, EXP_LEN, outputs, (int)OutputId::ENUM_COUNT, cylinders, (int)CylinderId::ENUM_COUNT);
    mb.registerConsumer(&o);
    Position p = Position(cylinders, (int)CylinderId::ENUM_COUNT);
    mb.registerConsumer(&p);
    Master m = Master(&mb);
    mb.registerConsumer(&m);
    MovePosition mp = MovePosition(&mb, 14, CylinderId::SPINNER_REAR, CylinderPosition::GROUND);
    mb.registerConsumer(&mp);
    MoveDirection md = MoveDirection(&mb, 14, CylinderId::SPINNER_REAR, CylinderDirection::UP, false);
    mb.registerConsumer(&md);



    while(true){
        mb.runProducers();
        mb.processMessageQueue();
    }
}