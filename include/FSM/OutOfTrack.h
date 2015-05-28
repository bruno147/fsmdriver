#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include <cmath>
#include "FSM.h"

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
    /** Auxiliar function to set class parameters
     * 
     * \param MAX_SKIDDING
     * \param NEGATIVE_ACCEL_PERCENT
     * \param VELOCITY_GEAR_4
     * \param VELOCITY_GEAR_3
     * \param VELOCITY_GEAR_2
     * \param MAX_RETURN_ANGLE
     * \param MIN_RETURN_ANGLE
     */
    void setParameters(float, float, int, int, int, float, float);
    //! Empty destructor
    ~OutOfTrack();

private:
    //! Parameters
    float MAX_SKIDDING;
    float NEGATIVE_ACCEL_PERCENT;
    int VELOCITY_GEAR_4;
    int VELOCITY_GEAR_3;
    int VELOCITY_GEAR_2;
    float MAX_RETURN_ANGLE;
    float MIN_RETURN_ANGLE;

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
