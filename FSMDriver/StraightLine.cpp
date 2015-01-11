#include "StraightLine.h"

StraightLine::StraightLine() {}

StraightLine::StraightLine(StraightLine const &) {}

StraightLine *StraightLine::instance() {
    static StraightLine instance;
    return &instance;
}

void StraightLine::enter(FSMDriver *driver) {
    cout << "Enter StraightLine" << endl;
}

void StraightLine::exit(FSMDriver *driver) {
    cout << "Exit StraightLine" << endl;
}

CarControl StraightLine::drive(FSMDriver *fsmdriver, CarState &cs) {
    const float accel = 1, brake = 0, clutch = 0;
    const int focus = 0, meta = 0;
    float steer = cs.getAngle();

    return CarControl(accel, brake, getGear(cs), steer, clutch, focus, meta);
}

float StraightLine::getBrake(CarState &cs) {
    return (cs.getSpeedX() < -2 ? 1:0);
}

bool StraightLine::shouldDecreaseGear(int currentGear, int rpm) {
    if(isLowGear(currentGear) && runningOnLow(rpm)) return true;
    if(isHighGear(currentGear) && runningUnderAverage(rpm)) return true;
    return false;
}

int StraightLine::getGear(CarState &cs) {
    int gear = cs.getGear();
    if(gear <= 0) return START_GEAR;

    int rpm = cs.getRpm();

    if(shouldIncreaseGear(gear, rpm)) ++gear;
    else if(shouldDecreaseGear(gear, rpm)) --gear;

    return gear;
}

StraightLine::~StraightLine() {}