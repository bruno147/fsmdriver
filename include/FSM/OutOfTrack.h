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

class FSMDriver3;
/*! \class OutOfTrack
 *  \brief OutOfTrack State Class.
 *
 *  Class to treat the state where the car is out of the track. Note that this state is important go back to the race in case of collisions and eventual driver's mislead 
 */
class OutOfTrack : public DrivingState<FSMDriver3> {
public:
    /** Create a pointer to the state to accomplish the singleton.
    */
    static OutOfTrack *instance();
    /** Function to indicate that the drive started at OutOfTrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void enter(FSMDriver3 *driver);
    /** Function to indicate that the drive leave the OutOfTrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void exit(FSMDriver3 *driver);
    /** Main function at state to drive the car.
    * \param fsmdriver3 is a pointer of the object of the driver itself,  
    * \param cs a data structure cointaining information from the car's sensors.
    */
    virtual CarControl drive(FSMDriver3 *fsmdriver3, CarState &cs);
    //! Empty destructor
    ~OutOfTrack();

private:
    //! Empty constructor.
    OutOfTrack();
    //! Construct from parameters.
    OutOfTrack(OutOfTrack const &);
    void operator=(OutOfTrack const&);

    float getBrake(CarState &cs);
    float getAccel(CarState &cs);
    int getGear(CarState &cs);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
