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
        const float accel = 1, brake = 0, clutch = 0;
        const int gear = -1, focus = 0, meta = 0;

        float steer = getSteer(cs);

        return CarControl(accel, brake, gear, steer, clutch, focus, meta);
	}

    ~Stuck(){}

private:
	float getSteer(CarState & cs){
        return (cs.getTrackPos() > 0 ? 1 : -1);
	}
};
#endif // FSMDRIVER_STATE_STUCK_H
