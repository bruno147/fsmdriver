#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include <cmath>
#include "FSM.h"


/******************************************************************************/
extern float MAX_SKIDDING; // = 3;
extern float NEGATIVE_ACCEL_PERCENT; // = 0.1;
extern int VELOCITY_GEAR_4; // = 90;
extern int VELOCITY_GEAR_3; // = 70;
extern int VELOCITY_GEAR_2; // = 40;
extern float MAX_RETURN_ANGLE; // = 0.7;
extern float MIN_RETURN_ANGLE; // = 0.5;
/******************************************************************************/

class FSMDriver;

class OutOfTrack : public DrivingState<FSMDriver> {
public:
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
