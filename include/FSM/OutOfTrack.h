/**  @file: OutOfTrack.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H
#define UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H

#include <cmath>
#include "DrivingState.h"

/**
 * Handles the driving when the car is outside track limits.
 *
 * @todo proper description
 * @todo proper documentation
 */
class OutOfTrack : public DrivingState {
public:
    /** Constructor.
     *
     * @param max_skidding
     * @param negative_accel_percent
     * @param velocity_gear_4
     * @param velocity_gear_3
     * @param velocity_gear_2
     * @param max_return_angle
     * @param min_return_angle
     */
    OutOfTrack(float _ms = 3, float _nap = 0.1, int _vg4 = 90,
               int _vg3 = 70, int _vg2 = 40, float _maxra = 0.7,
               float _minra = 0.5);
    //! Construct from parameters.
    // OutOfTrack(OutOfTrack const &);
    // void operator=(OutOfTrack const&);


    /* Inherited documentation. */
    CarControl drive(CarState &);

    /** Auxiliar function to set class parameters
     *
     * @param max_skidding
     * @param negative_accel_percent
     * @param velocity_gear_4
     * @param velocity_gear_3
     * @param velocity_gear_2
     * @param max_return_angle
     * @param min_return_angle
     */
    void setParameters(float, float, int, int, int, float, float);
    //! Empty destructor
    ~OutOfTrack();

public:
    //! Parameters
    /** @todo documentar
     *  @todo deixar argumentos privados. 
     */
    float max_skidding;
    float negative_accel_percent;
    int velocity_gear_4;
    int velocity_gear_3;
    int velocity_gear_2;
    float max_return_angle;
    float min_return_angle;

private:
    float getBrake(CarState &cs);
    float getAccel(CarState &cs);
    int getGear(CarState &cs);
    float getSteer(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H
