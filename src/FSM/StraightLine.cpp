#include "StraightLine.h"

int StraightLine::START_GEAR = 1;
int StraightLine::LOW_GEAR_LIMIT = 4;
int StraightLine::LOW_RPM = 1500;
int StraightLine::AVERAGE_RPM = 4000;
int StraightLine::HIGH_RPM = 9500;

StraightLine::StraightLine(int _sg, int _lgl, int _lrpm, int _arpm, int _hrpm) {
    START_GEAR = _sg;
    LOW_GEAR_LIMIT = _lgl;
    LOW_RPM = _lrpm;
    AVERAGE_RPM = _arpm;
    HIGH_RPM = _hrpm;
}

StraightLine::StraightLine(StraightLine const &) {}

CarControl StraightLine::drive(FSMDriver5 *FSMDriver5, CarState &cs) {
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
