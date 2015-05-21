/**  @file: InsideTrack.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#ifndef UNB_FSMDRIVER_STATE_INSIDE_TRACK_H
#define UNB_FSMDRIVER_STATE_INSIDE_TRACK_H

#include "DrivingState.h"

/** @todo Should not be using global variables. FIX THIS!!!!! */
extern int START_GEAR;
extern int LOW_GEAR_LIMIT;
extern int LOW_RPM;
extern int AVERAGE_RPM;
extern int HIGH_RPM;
// extern int currentGear;
extern float BASE_SPEED;
extern float SPEED_FACTOR;


/** Implements the behavior for a driver that is inside the track limits, THIS CLASS MUST BE
 * PROPERLY IMPLEMENTED! Singleton implementation aims to have one instance of
 * state for possibly many users. @todo FIX THIS!!!!! */
class InsideTrack : public DrivingState {
public:
    /** Returns a pointer to the singleton for this state. */
    static InsideTrack *instance();

    /** Destructor. */
    ~InsideTrack();

    /* Inherited. */
    CarControl drive(BaseDriver *, CarState &);

private:
    /* Private functions (singleton pattern). */
    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);

    int currentGear;
    float distance, targetSpeed;


    /** Defines the acceleration according to its perception.
     * @param cs Driver's perception of the environment. */
    float getAccel(CarState &cs);

    /** Defines the breaking according to its perception.
     * @param cs Driver's perception of the environment. */
    float getBrake(CarState cs);

    /** Defines the gear according to its perception.
     * @param cs Driver's perception of the environment. */
    int getGear(CarState &cs);

    /** Defines the steering according to its perception.
     * @param cs Driver's perception of the environment. */
    float getSteer(CarState &cs);

    void setTargetSpeed(CarState &cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);
};

#endif // UNB_FSMDRIVER_STATE_INSIDETRACK_H
