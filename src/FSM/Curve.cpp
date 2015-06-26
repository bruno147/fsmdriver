/**  @file: Curve.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "Curve.h"

Curve::Curve() : current_gear(StraightLine::start_gear) {
    /* Nothing. */
}

CarControl
Curve::drive(CarState &cs) {
	float steer = getSteer(cs);
	int gear = StraightLine::getGear(cs);
	float accel  = getAccel(cs);
    float brake = getBrake(cs);
	float clutch = 0;

	return CarControl(accel, brake, gear, steer, clutch);
}

float
Curve::getAccel(CarState &cs) {
    float curveAccel = 0.6;
	return curveAccel;
}

bool
Curve::isFacingWrongWay(CarState &cs) {
    return cs.getAngle() < -M_PI/2 || cs.getAngle() > M_PI/2;
}

float
Curve::getBrake(CarState cs) {
	return (cs.getSpeedX() < 0 ? 1:0);
}

float
Curve::findFarthestDirection(CarState &cs) {
    float farthestSensor = -INFINITY;
    float farthestDirection = 0;
    for (int i = 0; i < 19; i++) {
        if (farthestSensor < cs.getTrack(i)) {
            farthestSensor = cs.getTrack(i);
            farthestDirection = i;
        }
    }
    farthestDirection = -M_PI/2 + farthestDirection*M_PI/18;
    return normalizeSteer(-farthestDirection);
}

float
Curve::normalizeSteer(float angle) {
    const float maxsteer = 0.785398;
    return angle/maxsteer;
}
/** The steer is a essential actuator, getSteer obtain it using the track sensors to get the higher one and aplied that sensor's angle.*/
float
Curve::getSteer(CarState &cs) {
    return isFacingWrongWay(cs) ? cs.getAngle() : findFarthestDirection(cs);
}

Curve::~Curve() {
    /* Nothing. */
}
