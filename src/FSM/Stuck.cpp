/**  @file: Stuck.cpp
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#include "Stuck.h"

Stuck::Stuck(FSMDriver *o, float ss, int mrd, int mst, int msst)
            : DrivingState(o), stuck_speed(ss), minimum_distance_raced(mrd),
              maximum_number_of_ticks_stuck(mst), maximum_number_of_ticks_in_slow_speed(msst),
              elapsedTicks(0), slowSpeedTicks(0), trackInitialPos(0) {
}

Stuck::~Stuck() {
    /* Nothing */
}

CarControl
Stuck::drive(CarState &cs) {
    ++elapsedTicks;

    trackInitialPos = getInitialPos(cs);

    if(notStuckAnymore(cs) || hasBeenStuckLongEnough()){
        elapsedTicks = 0;
        slowSpeedTicks = 0;
        trackInitialPos = 0;
    }

    const float accel = 1, brake = 0, clutch = 0;
    const int gear = -1, focus = 0, meta = 0;
    float steer = getSteer(trackInitialPos, cs);

    return CarControl(accel, brake, gear, steer, clutch, focus, meta);
}

bool
Stuck::justStartedRace(CarState &cs) {
    return (cs.getDistRaced() <= minimum_distance_raced);
}

bool
Stuck::onRightWay(float trackPos, float angle) {
    return (((trackPos < 0) && (angle > -1.57) && (angle < 0)) ||
            ((trackPos > 0) && (angle < 1.57 ) && (angle > 0)) ||
            ((trackPos > 1) && (angle > 0))||
            ((trackPos < -1) && (angle < 0)));
}

/* @todo give this test (and the previous ones) with a meaningful name... */
bool
Stuck::notStuckAnymore(CarState &cs) {
    return onRightWay(cs.getTrackPos(), cs.getAngle());
}

bool
Stuck::hasBeenStuckLongEnough() {
    return (elapsedTicks >= maximum_number_of_ticks_stuck);
}

bool Stuck::isStuck(CarState &cs) {
    return (seemsStuck(cs) && !justStartedRace(cs));
}

float
Stuck::getSteer(float trackInitialPos, CarState &cs){
    if(abs(cs.getAngle()) > 1.557) // around 180 graus
        return (trackInitialPos > 0 ? -1 : 1);

    return (trackInitialPos > 0 ? 1 : -1);
}

bool
Stuck::seemsStuck(CarState &cs) {
    if(cs.getSpeedX() < stuck_speed)
        ++slowSpeedTicks;
    else
        slowSpeedTicks = 0;

    if(notStuckAnymore(cs))
        slowSpeedTicks = 0;

    return (slowSpeedTicks > maximum_number_of_ticks_in_slow_speed);
}

float
Stuck::getInitialPos(CarState &cs) {
	return (trackInitialPos == 0 ? cs.getTrackPos() : trackInitialPos);
}

