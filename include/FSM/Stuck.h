/**  @file: Stuck.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#ifndef UNB_FSMDRIVER_STATE_STUCK_H
#define UNB_FSMDRIVER_STATE_STUCK_H

#include "DrivingState.h"


/** @todo Should not be using global variables. FIX THIS!!!!! */
extern float STUCK_SPEED;
extern unsigned int MIN_RACED_DISTANCE;
extern unsigned int MAX_STUCK_TICKS;
extern unsigned int STUCK_THRESHOLD_TICKS;


/** Implements the behavior for a driver that is stuck, THIS CLASS MUST BE
 * PROPERLY IMPLEMENTED! Singleton implementation aims to have one instance of
 * state for possibly many users, so ticksElapsedWhileStuck, elapsedTicks, trackInitialPos
 * cannot store information of a single user. @todo FIX THIS!!!!! */
class Stuck : public DrivingState {
public:
    /** Returns a pointer to the singleton for this state. */
    static Stuck *instance();

    /** Destructor. */
    ~Stuck();

    /* Inherited. */
    void enter(BaseDriver *, CarState &);

	/* Inherited. */
    CarControl drive(BaseDriver *, CarState &);

    /** Indicates whether the driver is stuck according to its perception.
     * @param cs Driver's perception of the environment. */
	bool isStuck(CarState &cs);

private:
    /* Private functions (singleton pattern). */
    Stuck();
    Stuck(const Stuck &s);
    void operator=(const Stuck &s);

    unsigned int elapsedTicks;
    unsigned int ticksElapsedWhileStuck;
    float trackInitialPos;

    void updateState(CarState &cs);

	float getSteer(CarState &cs);
	float getInitialPos(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_STUCK_H
