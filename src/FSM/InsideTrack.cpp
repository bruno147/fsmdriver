/**  @file: InsideTrack.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#include <cmath>

#include "InsideTrack.h"

float SPEED_FACTOR = 1.4;

/******************************************************************************
 * Helper functions.                                                          *
 ******************************************************************************/

inline
void initialize_variables() {
    START_GEAR = 1;
    LOW_GEAR_LIMIT = 4;
    LOW_RPM = 1500;
    AVERAGE_RPM = 4000;
    HIGH_RPM = 9500;
    BASE_SPEED = 83;
    SPEED_FACTOR = 1.4;
}

inline
bool runningOnLow(int rpm) {
    return (rpm < LOW_RPM);
}

inline
bool runningUnderAverage(int rpm) {
    return (rpm <= AVERAGE_RPM);
}

inline
bool runningOnHigh(int rpm) {
    return (rpm > HIGH_RPM);
}

inline
bool isLowGear(int gear) {
    return (gear > START_GEAR && gear < LOW_GEAR_LIMIT);
}

inline
bool isHighGear(int gear) {
    return (gear >= LOW_GEAR_LIMIT);
}

inline
bool shouldIncreaseGear(int currentGear, int rpm) {
    return runningOnHigh(rpm);
}

inline
bool shouldDecreaseGear(int currentGear, int rpm) {
    if(isLowGear(currentGear) && runningOnLow(rpm)) return true;
    if(isHighGear(currentGear) && runningUnderAverage(rpm)) return true;
    return false;
}

/** isFacingWrongWay verify if the car is driving the right path, once it is possible
* that the car collide and turn to the opposite way.
* /param cs a data structure cointaining information from the car's sensors.
*/
inline
bool isFacingWrongWay(CarState &cs) {
    /** @todo "Same" as Stuck::facingTheRightWay ? can the code be reused? */
    return (cs.getAngle() < -M_PI/2) || (cs.getAngle() > M_PI/2);
}

/******************************************************************************/

InsideTrack::InsideTrack() : currentGear(START_GEAR) {
    initialize_variables();
}

InsideTrack::InsideTrack(InsideTrack const &) : currentGear(START_GEAR) {
    initialize_variables();
}

InsideTrack::~InsideTrack() {}

InsideTrack *InsideTrack::instance() {
    static InsideTrack instance;
    return &instance;
}

/** @todo Describe this. */
CarControl InsideTrack::drive(BaseDriver *driver, CarState &cs) {
	float steer = getSteer(cs);
    setTargetSpeed(cs);
	int gear = getGear(cs);
	float accel  = getAccel(cs);
    float brake = getBrake(cs);
	float clutch = 0;
    cout << "speed: " << this->targetSpeed << endl;
	return CarControl(accel, brake, gear, steer, clutch);
}

float InsideTrack::getSteer(CarState &cs) {
    return isFacingWrongWay(cs) ? cs.getAngle() : findFarthestDirection(cs);
}

int InsideTrack::getGear(CarState &cs) {
    int gear = cs.getGear();
    if(gear <= 0) return START_GEAR;

    int rpm = cs.getRpm();

    if(shouldIncreaseGear(gear, rpm))
        return gear + 1;

    if(shouldDecreaseGear(gear, rpm))
        return gear - 1;

    return gear;
}

float InsideTrack::getAccel(CarState &cs) {
    /** @todo Change accelaration logic. */
    /** @todo make code clearer. */
    return cs.getSpeedX() > targetSpeed ? 0 : 1;
}

float InsideTrack::getBrake(CarState cs) {
    /** @todo make code clearer. */
    return cs.getSpeedX() > targetSpeed ? 0.3 : 0;
}

void InsideTrack::setTargetSpeed(CarState &cs) {
    /** @todo make code clearer. */
    targetSpeed = BASE_SPEED + SPEED_FACTOR*distance;
}

float InsideTrack::findFarthestDirection(CarState &cs) {
    /** @todo make code clearer. */
    float farthestSensor = -INFINITY;
    float farthestDirection = 0;
    for (int i = 0; i < 19; i++) {
        if (farthestSensor < cs.getTrack(i)) {
            farthestSensor = cs.getTrack(i);
            farthestDirection = i;
        }
    }
    distance = farthestSensor;
    farthestDirection = -M_PI/2 + farthestDirection*M_PI/18;
    return normalizeSteer(-farthestDirection);
}

float InsideTrack::normalizeSteer(float angle) {
    /** @todo make code clearer. */
    const float MAX_STEER = 0.785398;
    return angle/MAX_STEER;
}
