/**  @file: ApproachingCurve.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "ApproachingCurve.h"

ApproachingCurve::ApproachingCurve(int _ms, int _tp, int _bs) {
    setParameters(_ms, _tp, _bs);
}

CarControl
ApproachingCurve::drive(CarState &cs) {
    if(!sensors_are_updated) /*@todo Só atualiza na 1a vez mesmo? */
        updateSensors(cs);

    const int focus = 0, meta = 0;
    const float clutch = 0;

    return CarControl(getAccel(cs), getBrake(cs), getGear(cs), cs.getAngle(), clutch, focus, meta);
    // Use the line below if the behavior of adjusting the car to the curve ahead is desired (not fully functional):
    // return CarControl(getAccel(cs), getBrake(cs), getGear(cs), getSteering(cs), clutch, focus, meta);
}

void
ApproachingCurve::setParameters(int _ms, int _tp, int _bs)
{
    max_steering = _ms;
    target_pos = _tp;
    base_speed = _bs;
}

void
ApproachingCurve::updateSensors(CarState &cs) {
    float speedFactor = 5000;                       // The target speed is obtained through a constant factor

    if (cs.getFocus(2) == -1) {                     // Focus sensors are available only once per second
        r_sensor = cs.getTrack(10);                  // Use track sensors
        c_sensor = cs.getTrack(9);
        l_sensor = cs.getTrack(8);
    }
    else {
        r_sensor = cs.getFocus(3);                   // Use focus sensors
        c_sensor = cs.getFocus(2);
        l_sensor = cs.getFocus(1);
    }
    target_speed = base_speed + speedFactor / fabs(l_sensor - r_sensor);

    sensors_are_updated = true;
}

float
ApproachingCurve::getSteering(CarState &cs) {
    if(r_sensor == l_sensor) return 0;

    float angle = cs.getAngle();
    // If the controller is not in a pre-defined region amongst the inside limits of the track (between 0.7 and 0.9 with the current
    // set of values, normalized), than it will be adjusted to do so
    bool adjustedToCurve = ((fabs(cs.getTrackPos()) - target_pos >= 0) && (fabs(cs.getTrackPos()) - target_pos < 0.2));

    if(!adjustedToCurve) {
        if(approachingRightTurn())
            angle = max_steering - angle;
        else
            angle -= max_steering;
    }

    return angle;
}

float
ApproachingCurve::getBrake(CarState &cs) {
    float brake = 0;
    float brake_factor = 0.02;
    float diff = cs.getSpeedX() - target_speed;

    if (isGoingWrongWay(cs)) return 1;
    if (diff > 0) brake = brake_factor * diff;

    return brake;
}

inline int
ApproachingCurve::getGear(CarState &cs) {
    return StraightLine::getGear(cs);
}

inline float
ApproachingCurve::getAccel(CarState cs) {
    return (cs.getSpeedX() > target_speed ? 0 : 1);
}

inline bool
ApproachingCurve::isGoingWrongWay(CarState cs) {
    return (cs.getSpeedX() < 0);

}
inline bool
ApproachingCurve::approachingRightTurn() {
    return (r_sensor > l_sensor);
}

ApproachingCurve::~ApproachingCurve() {
    /* Nothing. */
}
