#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "WrapperBaseDriver.h"
#include "FSM.h"

/*! \class FSMDriver
*   \brief The driver itself.
*   
*   This class defines the driver based on a FSM.
*/
class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
private:
    //! Actuators values.
    float accel, brake, steer;
    int gear;

public:
    //! Called when the driver finishes the race. 
    virtual void onShutdown();
    //! Called when TORCS asks a race restart.
    virtual void onRestart();

    //! Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);
    //! Empty constructor.
    FSMDriver();
    //! Construct from parameters.
    FSMDriver(int, char**);
    //! Empty destructor
    virtual ~FSMDriver(){}
    //! Transitions between states.
    /*!  
    *   This method decides whenever the current state does not fit with
    *   the car status and needs to be changed.
    *   \param cs a data structure cointaining information from the car's sensors.
    */
    void transition(CarState &cs);

    //! Main driving function.
    /*! \param cs a data structure cointaining information from the car's sensors.
    *   \return The data structure cointaining values for the car's actuators.
    */
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
