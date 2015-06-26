/**  @file: InsideTrack.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_STATE_INSIDE_TRACK_H
#define UNB_FSMDRIVER_STATE_INSIDE_TRACK_H

#include <cmath>
#include "DrivingState.h"

/**
 * Handles the driving when the car is within track limits.
 *
 * @todo proper description
 * @todo proper documentation
 */
class InsideTrack : public DrivingState {
public:
    /* Constructor
     *
     * Call setParameters
     */
    InsideTrack(int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                int _arpm = 4000, int _hrpm = 9000, float _bs = 83,
                float _sf = 1.4);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    /** Auxiliar function to obtain the gear analysing the car's rpm.
    */
    int getGear(CarState &cs);
    /** Auxiliar function to set class parameters
     *
     * @param start_gear
     * @param low_gear_limit
     * @param low_rpm
     * @param average_rpm
     * @param high_rpm
     * @param base_speed
     * @param speed_factor
     */
    void setParameters(int, int, int, int, int, float, float);
    //! Empty destructor
    ~InsideTrack();

private:
    //! Parameters
    int start_gear;
    int low_gear_limit;
    int low_rpm;
    int average_rpm;
    int high_rpm;
    float base_speed;
    float speed_factor;


    int current_gear;
    float distance, target_speed;

    bool shouldDecreaseGear(int current_gear, int rpm);
    bool runningOnLow(int rpm);
    bool runningUnderAverage(int rpm);
    bool runningOnHigh(int rpm);
    bool isLowGear(int gear);
    bool isHighGear(int gear);
    bool shouldIncreaseGear(int current_gear, int rpm);
    float getAccel(CarState &cs);
    void setTargetSpeed(CarState &cs);
    /** isFacingWrongWay verify if the car is driving the right path, once it is possible
    *   that the car collide and turn to the opposite way.
    * /param cs a data structure cointaining information from the car's sensors.
    */
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
