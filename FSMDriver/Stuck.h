#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "FSM.h"

class FSMDriver;

class Stuck : public DrivingState<FSMDriver> {
public:
    static Stuck *instance() {
        static Stuck instance;
        return &instance;
    }

private:
    Stuck() {}
    Stuck(Stuck const &);
    void operator=(Stuck const&);

public:
    void enter(FSMDriver *driver) {
        std::cout << "Enter Stuck" << std::endl;
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit Stuck" << std::endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
	    return CarControl(1, 0, -1, this->getSteer(cs), 0, 0, 0);
	}

    ~Stuck(){}

private:
	float getSteer(CarState & cs){
        return (cs.getTrackPos() > 0 ? 1 : -1);
	}
};
#endif // FSMDRIVER_STATE_STUCK_H
