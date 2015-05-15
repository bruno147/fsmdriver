#include "StraightLine.h"

// int START_GEAR = 1;
// int LOW_GEAR_LIMIT = 4;

// int LOW_RPM = 1500;
// int AVERAGE_RPM = 4000;
// int HIGH_RPM = 9500;

StraightLine::StraightLine() {}

StraightLine::StraightLine(StraightLine const &) {}

StraightLine *StraightLine::instance() {
    static StraightLine instance;
    return &instance;
}

void StraightLine::enter(FSMDriver *driver) {
    //cout << "Enter StraightLine" << endl;
}

void StraightLine::exit(FSMDriver *driver) {
    //cout << "Exit StraightLine" << endl;
}

CarControl StraightLine::drive(FSMDriver *FSMDriver, CarState &cs) {
    const float accel = 1, brake = 0, clutch = 0;
    const int focus = 0, meta = 0;
    float steer = cs.getAngle();

    return CarControl(accel, brake, getGear(cs), steer, clutch, focus, meta);
}

bool StraightLine::shouldDecreaseGear(int currentGear, int rpm) {
    if(isLowGear(currentGear) && runningOnLow(rpm)) return true;
    if(isHighGear(currentGear) && runningUnderAverage(rpm)) return true;
    return false;
}

float StraightLine::getBrake(CarState &cs) {
    return (cs.getSpeedX() < 0 ? 1:0);
}

int StraightLine::getGear(CarState &cs) {
    int gear = cs.getGear();
    if(gear <= 0) return START_GEAR;

    int rpm = cs.getRpm();

    if(shouldIncreaseGear(gear, rpm)) ++gear;
    else if(shouldDecreaseGear(gear, rpm)) --gear;

    return gear;
}

inline bool StraightLine::runningOnLow(int rpm) {
    return (rpm < LOW_RPM);
}

inline bool StraightLine::runningUnderAverage(int rpm) {
    return (rpm <= AVERAGE_RPM);
}

inline bool StraightLine::runningOnHigh(int rpm) {
    return (rpm > HIGH_RPM);
}

inline bool StraightLine::isLowGear(int gear) {
    return (gear > START_GEAR && gear < LOW_GEAR_LIMIT);
}

inline bool StraightLine::isHighGear(int gear) {
    return (gear >= LOW_GEAR_LIMIT);
}

inline bool StraightLine::shouldIncreaseGear(int currentGear, int rpm) {
    return runningOnHigh(rpm);
}

StraightLine::~StraightLine() {}
