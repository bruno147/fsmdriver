#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "State.h"

class Stuck : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver) {
	    CarState& cs = fsmdriver->getCarState();
	    CarControl cc();
	    return cc;
	}

    ~Stuck(){}
    Stuck(){}


#endif // FSMDRIVER_STATE_OUTOFTRACK_H