#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "State.h"

class Stuck : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver) {
	    CarState& cs = fsmdriver->getCarState();
	    CarControl cc(1, 0, -1, this->getSteer(cs), 0, 0, 0);
	    return cc;
	}
    static Stuck* Instance() {
        static Stuck instance;
        return &instance;
    }

    ~Stuck(){}
private:
    Stuck(){}
	float getSteer(CarState & cs){
		if(cs.getTrackPos()>0){
			return 1;
		}else{
			return -1;
		}
	}
};
#endif // FSMDRIVER_STATE_STUCK_H
