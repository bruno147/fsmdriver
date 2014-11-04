#ifndef FSMDRIVER_STATE_STRAIGHTLINE_H
#define FSMDRIVER_STATE_STRAIGHTLINE_H

#include "FSM.h"

const int START_GEAR = 1;
const int LOW_GEAR_LIMIT = 4;

const int LOW_RPM = 1500;
const int AVERAGE_RPM = 4000;
const int HIGH_RPM = 9500;

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

        return CarControl(accel, brake, getGear(cs), getSteer(cs), clutch, focus, meta);
    }

private:
    static inline bool runningOnLow(int rpm) {
        return (rpm < LOW_RPM);
    }
    static inline bool runningOnHigh(int rpm) {
        return (rpm > HIGH_RPM);
    }
    static inline bool runningUnderAverage(int rpm) {
        return (rpm <= AVERAGE_RPM);
    }
    static inline bool isLow(int gear) {
        return (gear <= LOW_GEAR_LIMIT);
    }
    static inline bool shouldIncreaseGear(int gear, int rpm) {
        return runningOnHigh(rpm);
    }
    static inline bool shouldDecreaseGear(int gear, int rpm) {
        return (isLow(gear) ? runningOnLow(rpm) : runningUnderAverage(rpm));
    }

	float getSteer(CarState & cs) {
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

public:
    static int getGear(CarState &cs) {
        int gear = cs.getGear();
        if(!gear) return START_GEAR;

        int rpm = cs.getRpm();

        if(shouldIncreaseGear(gear, rpm)) ++gear;
        else if(shouldDecreaseGear(gear, rpm)) --gear;

        return gear;
    }
};

#endif // FSMDRIVER_STATE_STRAIGHTLINE_H
