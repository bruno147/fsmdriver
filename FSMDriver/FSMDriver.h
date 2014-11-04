#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "WrapperBaseDriver.h"
#include "FSM.h"

class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
private:
    float accel, brake, steer; //Actuators values
    int gear;

    static const float  LEFT_EDGE;
    static const float  RIGHT_EDGE;
    static const float  MAX_SPEED_DIST;
    static const float  MAX_STR_ANGLE;
    static const float  MIN_STR_ANGLE;
    static const int    STUCK_TICKS;

public:
    CarState cs;
    virtual void onShutdown();
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    FSMDriver();
    virtual ~FSMDriver(){}

    // Transitions between states (if appropriate).
    void transition(CarState &);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
