#ifndef UNB_FSMDRIVER_FSMDRIVER_H
#define UNB_FSMDRIVER_FSMDRIVER_H

#include "DrivingFSM.h"
#include "WrapperBaseDriver.h"

/** Defines a a driver whose behavior is modeled by a DrivingFSM. */
class FSMDriver : public WrapperBaseDriver {
public:
    /** Constructor. */
    FSMDriver() : fsm(this) {}

    /** Destructor. */
    virtual ~FSMDriver() {};

    /** Transitions between states, according to the current perception.
     * @param cs Driver's perception of the environment. */
    virtual void transition(CarState &cs) = 0;

protected:
    /** Defines the driver's behavior. */
    DrivingFSM fsm;
};

#endif // UNB_FSMDRIVER_FSMDRIVER_H
