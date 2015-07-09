/**  @file: ApproachingCurve.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
#define UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H

#include <cmath>
#include "DrivingState.h"
#include "StraightLine.h"

/**
* @brief ApproachingCurve state
* @details Class to treat State where the section of the track before a curve, to better complete a curve it require a speed depending of the curve(for example how obligue it is)
*
* @param max_steering maximum allowed steering value.
* @param target_pos desired percentage position.
* @param base_speed lowest speed allowed during turns.
*/
class ApproachingCurve : public DrivingState {
public:
    ApproachingCurve(int _ms = 0, int _tp = 0, int _bs = 0);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    void setParameters(int, int, int);

    ~ApproachingCurve();

private:
    float max_steering, target_pos, base_speed;
    bool sensors_are_updated;
    float r_sensor, c_sensor, l_sensor, target_speed;

    void updateSensors(CarState &cs);
    float getSteering(CarState &cs);
    float getBrake(CarState &cs);

    inline bool isGoingWrongWay(CarState cs);
    inline int getGear(CarState &cs);
    inline float getAccel(CarState cs);
    inline bool approachingRightTurn();
};



#endif // UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
