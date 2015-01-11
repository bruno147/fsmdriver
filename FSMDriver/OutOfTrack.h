#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include <cmath>
#include "FSM.h"


class FSMDriver;

class OutOfTrack : public DrivingState<FSMDriver> {
public:   
    /******************************************************************************/
    static float MAX_SKIDDING;
    static float NEGATIVE_ACCEL_PERCENT;
    static float VELOCITY_GEAR_4;
    static float VELOCITY_GEAR_3;
    static float VELOCITY_GEAR_2;
    static float MAX_RETURN_ANGLE;
    static float MIN_RETURN_ANGLE;
    /******************************************************************************/
    
    static OutOfTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);

    ~OutOfTrack();

private:
    OutOfTrack();
    OutOfTrack(OutOfTrack const &);
    void operator=(OutOfTrack const&);

    float getBrake(CarState &cs);
    float getAccel(CarState &cs);
    int getGear(CarState &cs);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
