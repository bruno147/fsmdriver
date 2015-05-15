#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include <cmath>
#include "FSM.h"
#include "Constants.h"


class FSMDriver;
/*! \class OutOfTrack
 *  \brief OutOfTrack State Class.
 *
 *  Class to treat the state where the car is out of the track. Note that this state is important go back to the race in case of collisions and eventual driver's mislead 
 */
class OutOfTrack : public DrivingState<FSMDriver> {
public:
    /** Create a pointer to the state to accomplish the singleton.
    */
    static OutOfTrack *instance();
    /** Function to indicate that the drive started at OutOfTrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void enter(FSMDriver *driver);
    /** Function to indicate that the drive leave the OutOfTrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void exit(FSMDriver *driver);
    /** Main function at state to drive the car.
    * \param fsmdriver is a pointer of the object of the driver itself,  
    * \param cs a data structure cointaining information from the car's sensors.
    */
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
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
