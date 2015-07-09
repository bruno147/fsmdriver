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
 * @brief OutOfTrack state.
 * @details Handles the driving when the car is outside track limits. Since the outside the track the track's type change, like dirt road,
 * the driver losses performance that state manage to take the drive out of the track. 
 *
 * @param max_skidding defines the threshold to start to break to avoid skidding.
 * @param negative_accel_percent dictate how much to release the acceleration pedal to avoid to skidding,
 *                               its defined with the axis speed of car.
 * @param velocity_gear_4 threshold to change the gear to 4.
 * @param velocity_gear_3 threshold to change the gear to 3.
 * @param velocity_gear_2 threshold to change the gear to 2.
 * @param max_return_angle upper boundary to angle of return to track.
 * @param min_return_angle lower boundary to angle of return to track.
 */
class OutOfTrack : public DrivingState {
public:
    /** Constructor.
     *
     * Call setParameters
     * @param _ms (max_skidding), _nap (negative_accel_percent), _vg4 (velocity_gear_4), _vg3 (velocity_gear_3), _vg2 (velocity_gear_2), maxra (max_return_angle), minra (min_return_angle), description    * can be found bellow
     */
    OutOfTrack(float _ms = 3, float _nap = 0.1, int _vg4 = 90,
               int _vg3 = 70, int _vg2 = 40, float _maxra = 0.7,
               float _minra = 0.5);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    /** Auxiliar function to set class parameters
     *
     */
    void setParameters(float, float, int, int, int, float, float);
    //! Empty destructor
    ~OutOfTrack();

private:
    /** The car's skidding is measured by Yspeed, max_skidding is a constant to indicated how much the drive must brake  
    */
    float max_skidding;
    /** The negative_accel_percent is a proportinal factor to calculate accel
    */
    float negative_accel_percent;
    /** velocity_gear_4 is a constant that determine a speed which above it the gear must remain the same 
    */
    int velocity_gear_4;
    /** velocity_gear_3 is a constant that determine a speed which above it and bellow velocity_gear_3 the gear must be set 3
    */
    int velocity_gear_3;
    /** velocity_gear_2 is a constant that determine a speed which bellow it must be set 1
    */
    int velocity_gear_2;
    /** max_return_angle the a angle limit that turning steer to -1 or 1 depending the TrackPos sensor
    */
    float max_return_angle;
    /** min_return_angle the a angle limit that turning steer to -1 or 1 depending the TrackPos sensor
    */
    float min_return_angle;
    /** getBrake obtain the brake based on the Xspeed,Yspeed and max_skidding
    * @param cs the driver's perception of the environment.
    * @return 0 when the car' Xspeed and Yspeed is not high enough, 0.1 when the car has Yspeed 
    * higher enough and 1 when the car has Xspeed < 0	 
    */
    float getBrake(CarState &cs);
    /** getAccel calculate the accel based on the Yspeed and negative_accel_percent
    * @param cs the driver's perception of the environment.
    * @return the accel value proportinal to Yspeed	 
    */
    float getAccel(CarState &cs);
    /** getGear calculate the accel based on the Xspeed and speed limits to each gear, that way
    * high speed need high gear. Please note that outoftrack does not use rpm to obtain gear.
    * @param cs the driver's perception of the environment.
    * @return the a gear value accordingthe car's Xspeed	 
    */
    int getGear(CarState &cs);
    /** getSteer calculate the steer based on the trackPos sensor, that allow to know which track 
    * border the car is, and angle that allow to know which side turn the steer.
    * @param cs the driver's perception of the environment.
    * @return 1 or -1 to Steer value 
    */
    float getSteer(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H
