#ifndef FSMDRIVER_FSMDRIVER_3_H
#define FSMDRIVER_FSMDRIVER_3_H

#include "FSMDriver.h"

/** Defines a controller that uses a Finite State Machine with 3 states do model
 * its behavior. */
class FSMDriver3 : public FSMDriver {
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
    FSMDriver3();
    //! Construct from parameters.
    FSMDriver3(int, char**);
    //! Empty destructor
    virtual ~FSMDriver3(){}
    //! Transitions between states.
    /*!
    *   This method decides whenever the current state does not fit with
    *   the car status and needs to be changed.The transition choose the most fitted state at the moment of the race.
    *	Note that the transition move to each state with only one pointer to each of than, what is called singleton.
    *   \param cs a data structure cointaining information from the car's sensors.
    */

    void transition(CarState &cs);

    //! Main driving function.
    /*! \param cs a data structure cointaining information from the car's sensors.
    *   \return The data structure cointaining values for the car's actuators.
    */
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_FSMDRIVER_3_H
