/**  @file: Curve.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_STATE_CURVE_H
#define UNB_FSMDRIVER_STATE_CURVE_H

#include <cmath>
#include "DrivingState.h"
#include "StraightLine.h"

/** Class to treat curve state where the track has a minimal curvature. Note that this state is important at the race considering oponents with equal speed the way the driver complete the curve can achieve the lead at the race.*/
class Curve : public DrivingState {
public:
    Curve();

    /* Inherited documentation. */
    CarControl drive(CarState &);

    ~Curve();

private:
    int current_gear;

    float getAccel(CarState &cs);
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);/**Since the TORCS receive a value between -1 and 1 to the steer it used this function to normalize */
    float getSteer(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_CURVE_H
