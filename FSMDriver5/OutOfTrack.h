#ifndef FSMDriver5_STATE_OUTOFTRACK_H
#define FSMDriver5_STATE_OUTOFTRACK_H

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

class FSMDriver5;
/**Class to treat the state where the car is out of the track. Note that this state is important go back to the race in case of colligions and eventual driver's mislead */
class OutOfTrack : public DrivingState<FSMDriver5> {
public:
    static OutOfTrack *instance();
    void enter(FSMDriver5 *driver);
    void exit(FSMDriver5 *driver);
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);

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

#endif // FSMDriver5_STATE_OUTOFTRACK_H
