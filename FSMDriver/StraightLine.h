#ifndef FSMDRIVER_STATE_STRAIGHTLINE_H
#define FSMDRIVER_STATE_STRAIGHTLINE_H

#include <cmath>
#include "FSM.h"

const int START_GEAR = 1; 
const int DECREASE_GEAR_RPM = 1500;
const int AVERAGE_RPM = 4000;
const int INCREASE_GEAR_RPM = 9500;
const int LOW_GEAR_LIMIT = 4;

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
        const float accel = 1, brake = 0, clutch = 0;
        const int focus = 0, meta = 0;

        float steer = getSteering(cs);
        int gear = getGear(cs);

        return CarControl(accel, brake, gear, steer, clutch, focus, meta);
    }

private:
    static inline bool lowRPM(int rpm) {
        return (rpm < DECREASE_GEAR_RPM);
    }
    static inline bool subAverageRPM(int rpm) {
        return (rpm <= AVERAGE_RPM);
    }
    static inline bool highRPM(int rpm) {
        return (rpm > INCREASE_GEAR_RPM);
    }
    static inline bool lowGear(int gear) {
        return (gear <= LOW_GEAR_LIMIT);
    }
    static inline bool upGear(int gear, int rpm) {
        return highRPM(rpm);
    }
    static inline bool downGear(int gear, int rpm) {
        if(lowGear(gear)) return lowRPM(rpm);
        return subAverageRPM(rpm);
    }

	float getSteering(CarState & cs) {
        // based on Loiacono's SimpleDriver
        const float steerLock = 0.366519;
        float targetAngle = (cs.getAngle() - cs.getTrackPos() * 0.5) / steerLock;

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

public:
    static int getGear(CarState &cs) {
        int gear = cs.getGear();
        if(!gear) return START_GEAR;

        int rpm = cs.getRpm();

        if(upGear(gear, rpm)) ++gear;
        else if(downGear(gear, rpm)) --gear;

        return gear;
    }
};

#endif // FSMDRIVER_STATE_STRAIGHTLINE_H
