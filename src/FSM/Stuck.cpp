/**  @file: Stuck.cpp
 * @author: Bruno Macedo, Gabriel Araujo, Gabriel Sousa, Matheus Crestani, Yuri Galli, Guilherme N. Ramos (gnramos@unb.br)
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "Stuck.h"

Stuck::Stuck(float ss, int mrd, int mst, int msst)
            : stuck_speed(ss), minimum_distance_raced(mrd),
              maximum_number_of_ticks_stuck(mst), maximum_number_of_ticks_in_slow_speed(msst),
              elapsed_ticks(0), slow_speed_ticks(0), track_initial_pos(0) {
}

Stuck::~Stuck() {
    /* Nothing */
}

CarControl
Stuck::drive(CarState &cs) {
    ++elapsed_ticks;

    track_initial_pos = getInitialPos(cs);

    if(notStuckAnymore(cs) || hasBeenStuckLongEnough()){
        elapsed_ticks = 0;
        slow_speed_ticks = 0;
        track_initial_pos = 0;
    }

    const float accel = 1, brake = 0, clutch = 0;
    const int gear = -1, focus = 0, meta = 0;
    float steer = getSteer(track_initial_pos, cs);

    return CarControl(accel, brake, gear, steer, clutch, focus, meta);
}

bool
Stuck::justStartedRace(CarState &cs) {
    return (cs.getDistRaced() <= minimum_distance_raced);
}


// NUMEROS
bool
Stuck::onRightWay(float track_pos, float angle) {
    return (((track_pos < 0) && (angle > -1.57) && (angle < 0)) ||
            ((track_pos > 0) && (angle < 1.57 ) && (angle > 0)) ||
            ((track_pos > 1) && (angle > 0))||
            ((track_pos < -1) && (angle < 0)));
}

/* @todo give this test (and the previous ones) with a meaningful name... */
bool
Stuck::notStuckAnymore(CarState &cs) {
    return onRightWay(cs.getTrackPos(), cs.getAngle());
}

bool
Stuck::hasBeenStuckLongEnough() {
    return (elapsed_ticks >= maximum_number_of_ticks_stuck);
}

bool Stuck::isStuck(CarState &cs) {
    return (seemsStuck(cs) && !justStartedRace(cs));
}

float
Stuck::getSteer(float track_initial_pos, CarState &cs){
    if(abs(cs.getAngle()) > 1.557) // around 180 graus
        return (track_initial_pos > 0 ? -1 : 1);

    return (track_initial_pos > 0 ? 1 : -1);
}

bool
Stuck::seemsStuck(CarState &cs) {
    if(cs.getSpeedX() < stuck_speed)
        ++slow_speed_ticks;
    else
        slow_speed_ticks = 0;

    if(notStuckAnymore(cs))
        slow_speed_ticks = 0;

    return (slow_speed_ticks > maximum_number_of_ticks_in_slow_speed);
}

float
Stuck::getInitialPos(CarState &cs) {
	return (track_initial_pos == 0 ? cs.getTrackPos() : track_initial_pos);
}

