#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "WrapperBaseDriver.h"
#include "FSM.h"
#include <bitset>


class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
private:
    float accel, brake, steer; //Actuators values
    int gear;
    int segment_id;

    int MAX_STRAIGHT_LINE_VAR;
    int MIN_STRAIGHT_LINE_VAR;
    int MAX_APPROACHING_CURVE_VAR;
    int MIN_APPROACHING_CURVE_VAR;

    float    binToFloat (string bits);
    float    parameters[22];

public:
    virtual void onShutdown();
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    FSMDriver();
    FSMDriver(int, char**);
    virtual ~FSMDriver(){}

    // Transitions between states (if appropriate).
    void transition(CarState &);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
