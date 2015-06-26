/**  @file: StraightLine.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "StraightLine.h"

int StraightLine::start_gear = 1;
int StraightLine::low_gear_limit = 4;
int StraightLine::low_rpm = 1500;
int StraightLine::average_rpm = 4000;
int StraightLine::high_rpm = 9500;

StraightLine::StraightLine(int _sg, int _lgl, int _lrpm, int _arpm, int _hrpm) {
    setParameters(_sg, _lgl, _lrpm, _arpm, _hrpm);
}

CarControl
StraightLine::drive(CarState &cs) {
    const float accel = 1, brake = 0, clutch = 0;
    const int focus = 0, meta = 0;
    float steer = cs.getAngle();

    return CarControl(accel, brake, getGear(cs), steer, clutch, focus, meta);
}

void
StraightLine::setParameters(int _sg, int _lgl, int _lrpm, int _arpm, int _hrpm)
{
    start_gear = _sg;
    low_gear_limit = _lgl;
    low_rpm = _lrpm;
    average_rpm = _arpm;
    high_rpm = _hrpm;
}


bool
StraightLine::shouldDecreaseGear(int current_gear, int rpm) {
    if(isLowGear(current_gear) && runningOnLow(rpm)) return true;
    if(isHighGear(current_gear) && runningUnderAverage(rpm)) return true;
    return false;
}

float
StraightLine::getBrake(CarState &cs) {
    return (cs.getSpeedX() < 0 ? 1:0);
}

int
StraightLine::getGear(CarState &cs) {
    int gear = cs.getGear();
    if(gear <= 0) return start_gear;

    int rpm = cs.getRpm();

    if(shouldIncreaseGear(gear, rpm)) ++gear;
    else if(shouldDecreaseGear(gear, rpm)) --gear;

    return gear;
}

inline bool
StraightLine::runningOnLow(int rpm) {
    return (rpm < low_rpm);
}

inline bool
StraightLine::runningUnderAverage(int rpm) {
    return (rpm <= average_rpm);
}

inline bool
StraightLine::runningOnHigh(int rpm) {
    return (rpm > high_rpm);
}

inline bool
StraightLine::isLowGear(int gear) {
    return (gear > start_gear && gear < low_gear_limit);
}

inline bool
StraightLine::isHighGear(int gear) {
    return (gear >= low_gear_limit);
}

inline bool
StraightLine::shouldIncreaseGear(int current_gear, int rpm) {
    return runningOnHigh(rpm);
}

StraightLine::~StraightLine() {
    /* Nothing. */
}
