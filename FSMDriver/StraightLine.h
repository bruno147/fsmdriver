#ifndef FSMDRIVER_STATE_STRAIGHTLINE_H
#define FSMDRIVER_STATE_STRAIGHTLINE_H

#include <cmath>
#include "FSM.h"

class FSMDriver;

class StraightLine : public DrivingState<FSMDriver> {
public:
    static StraightLine *instance() {
        static StraightLine instance;
        return &instance;
    }

private:
    StraightLine() {}
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);

public:
    ~StraightLine(){}

    void enter(FSMDriver *driver) {
        std::cout << "Enter StraightLine" << std::endl;
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit StraightLine" << std::endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
        float brake = 0, clutch = 0;

        float steer = getSteering(cs);

        int gear = getGear(cs), focus = 0, meta = 0;

        CarControl cc(1, brake, gear, steer, clutch, focus, meta);

        return cc;
    }

private:
	int getGear(CarState & cs) {
        int current_gear = cs.getGear();
        if(!current_gear) return 1;

        if(current_gear > 1 && current_gear < 4 && cs.getRpm() < 1500)
            return(current_gear - 1);

        if(current_gear < 2 && cs.getRpm() > 9500)
            return(current_gear + 1);

        if(current_gear >= 2 && cs.getRpm() > 9500)
            return(current_gear + 1);

        if(current_gear >= 4 && cs.getRpm() < 4000)
            return(current_gear - 1);

        return current_gear;
    }

	float getSteering(CarState & cs) {
        // based on Loiacono's SimpleDriver

        const float
          steerLock = 0.366519;
        float
          targetAngle = (cs.getAngle() - cs.getTrackPos() * 0.5) / steerLock;

        // normalize steering
        if(targetAngle < -1)
            targetAngle = -1;
        else if(targetAngle > 1)
            targetAngle = 1;

        return targetAngle;
    }


    float getDistTrackAxis(CarState & cs) {
        return cs.getTrackPos();
    }

    float getSpeed(CarState & cs) {
        return sqrt(pow(cs.getSpeedX(), 2) + pow(cs.getSpeedY(), 2));
    }
};

#endif // FSMDRIVER_STATE_STRAIGHTLINE_H
