/**  @file: Stuck.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_STATE_STUCK_H
#define UNB_FSMDRIVER_STATE_STUCK_H

#include <cmath>

#include "DrivingState.h"

/**
 * Handles the driving when the car is stuck. This usually means it is stopped
 * or has been driving at a very low speed for a while.
 *
 * @todo proper documentation */
class Stuck : public DrivingState {
public:
    /** Constructor.
     *
     * Call setParameters
     *
     * @todo fix parameter descriptions */
    Stuck(float ss = 5.0, int mrd = 100, int mst = 300, int msst = 50);

    /** Destructor. */
    ~Stuck();

    /** @todo describe behavior */
    CarControl drive(CarState &);

    /** Indicates if the controller is stuck.
     *
     * @param cs the driver's perception of the environment.
     * @return true if the controller is stuck, false otherwise. */
    bool isStuck(CarState &cs);

    void setParameters(float ss, int mrd, int mst, int msst);

private:
    /** @todo proper documentation of attributes */
    float stuck_speed;
    unsigned int minimum_distance_raced;
    unsigned int maximum_number_of_ticks_stuck;
    unsigned int maximum_number_of_ticks_in_slow_speed;

    /** @todo proper documentation of attributes */
    bool seemsStuck(CarState &cs);
    bool justStartedRace(CarState &cs);
    bool onRightWay(float trackPos, float angle);
    bool notStuckAnymore(CarState &cs);
    bool hasBeenStuckLongEnough();
    float getSteer(float trackInitialPos, CarState &cs);
    float getInitialPos(CarState &cs);

    unsigned int elapsed_ticks;
    unsigned int slow_speed_ticks;
    float track_initial_pos;

};

#endif // UNB_FSMDRIVER_STATE_STUCK_H
