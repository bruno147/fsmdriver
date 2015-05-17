/**  @file: Stuck.cpp
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#include "Stuck.h"

/** @todo Rethink use of these variables, not compatible with singleton. */
float STUCK_SPEED = 5;
unsigned int MIN_RACED_DISTANCE = 100;
unsigned int MAX_STUCK_TICKS = 300;
unsigned int STUCK_THRESHOLD_TICKS = 50;


/*******************************************************************************
 * Helper functions.
 *******************************************************************************/
inline
bool raceJustStarted(CarState &cs) {
    return (cs.getDistRaced() <= MIN_RACED_DISTANCE);
}

inline
bool facingTheRightWay(float trackPos, float angle) {
    /** @todo make code clearer. */
    return (((trackPos < 0) && (angle > -1.57) && (angle < 0)) ||
            ((trackPos > 0) && (angle < 1.57 ) && (angle > 0)) ||
            ((trackPos > 1) && (angle > 0))||
            ((trackPos < -1) && (angle < 0)));
}

inline
bool notGettingUnstuck(unsigned int elapsedTicks) {
    return (elapsedTicks >= MAX_STUCK_TICKS);
}

inline
bool seemsStuck(unsigned int ticksElapsedWhileStuck) {
    return (ticksElapsedWhileStuck > STUCK_THRESHOLD_TICKS);
}
/*******************************************************************************/


Stuck::Stuck() : elapsedTicks(0),
                 ticksElapsedWhileStuck(0),
                 trackInitialPos(0) {}

Stuck::Stuck(const Stuck &s) : elapsedTicks(s.elapsedTicks),
                               ticksElapsedWhileStuck(s.ticksElapsedWhileStuck),
                               trackInitialPos(s.trackInitialPos) {}

Stuck::~Stuck() {}

Stuck *Stuck::instance() {
    static Stuck instance;
    return &instance;
}

/** Resets the elapsedTicks. */
void Stuck::enter(BaseDriver *driver, CarState &cs) {
    elapsedTicks = 0;
}

/** @todo remove dependencies of ticksElapsedWhileStuck */
bool Stuck::isStuck(CarState &cs) {
    return (!raceJustStarted(cs) && seemsStuck(ticksElapsedWhileStuck));
}

/** @todo describe implementation! */
CarControl Stuck::drive(BaseDriver *Driver, CarState &cs) {
    updateState(cs);

    const float accel = 1, brake = 0, clutch = 0;
    const int gear = -1, focus = 0, meta = 0;

    return CarControl(accel, brake, gear, getSteer(cs), clutch, focus, meta);
}

void Stuck::updateState(CarState &cs) {
    ++elapsedTicks;

    trackInitialPos = getInitialPos(cs);

    if(cs.getSpeedX() < STUCK_SPEED)
        ++ticksElapsedWhileStuck;
    else
        ticksElapsedWhileStuck = 0;

    if(facingTheRightWay(cs.getTrackPos(), cs.getAngle()) || notGettingUnstuck(elapsedTicks)){
        elapsedTicks = 0;
        ticksElapsedWhileStuck = 0;
        trackInitialPos = 0;
    }
}

float Stuck::getSteer(CarState &cs) {
    const float FULL_TURN = 1.557; // around 180 graus

    float angle = cs.getAngle();
    if(angle < 0)
        angle = -angle;

    /** @todo make code clearer. */
    if(angle > FULL_TURN)
	   return (trackInitialPos > 0 ? -1 : 1);

	return (trackInitialPos > 0 ? 1 : -1);
}

float Stuck::getInitialPos(CarState &cs){
    /** @todo make code clearer. */
	return (trackInitialPos ? trackInitialPos : cs.getTrackPos());
}
