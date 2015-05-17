#ifndef FSMDRIVER_STATE_H
#define FSMDRIVER_STATE_H

#include "BaseDriver.h"
#include "CarControl.h"
#include "CarState.h"

/** Abstract class for defining a driving state for the FSM. */
class DrivingState {
public:
	/** Destructor. */
    virtual ~DrivingState() {}

    /** Implements the driving behavior of the state.
     * @param driver Pointer to the driver using the state.
     * @param cs Driver's perception of the environment.
     * @return The driver's actions. */
    virtual CarControl drive(BaseDriver *driver, CarState &cs) = 0;

    /** Called when entering the state.
     * @param driver Pointer to the driver using the state. */
    virtual void enter(BaseDriver *driver) {}

    /** Called when exiting the state.
     * @param driver Pointer to the driver using the state. */
    virtual void exit(BaseDriver *driver) {}
};

#endif // FSMDRIVER_STATE_H
