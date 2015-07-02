/**  @file: FSMDriver.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "FSMDriver.h"
// TODO new method for choose dirt or road track
FSMDriver::FSMDriver() : current_state(nullptr), previous_state(nullptr), tested(UNKN), threshold(11.6035) {
}

FSMDriver::~FSMDriver() {
	/* Nothing */
}

void
FSMDriver::changeTo(DrivingState *state) {
	assert(state);
	previous_state = current_state;
	current_state = state;
}

void
FSMDriver::revertState() {
	changeTo(previous_state);
}

CarControl
FSMDriver::wDrive(CarState cs) {
    transition(cs);
    if(tested == UNKN && stage == BaseDriver::WARMUP)   return testTrack(cs);
    else    return current_state->drive(cs);
}

CarControl
FSMDriver::testTrack(CarState cs)
{
    static bool flag = false, flag2 = false;
    float accel = 1, steer = 0, brake = 0, clutch = 0;
    int gear = 1, focus = 0, meta = 0;

    if(cs.getSpeedX() >= 80) {
        flag2 = true;
        if(!flag){
            dist = cs.getDistRaced();
            flag = true;
        }
    }
    if(cs.getSpeedX() <= 2 && flag2) {
        dist = dist - cs.getDistRaced();
        // cout << "Dist = " << dist << endl;
        if(-dist < threshold)   tested = ROAD;
        else                    tested = DIRT;
    }
    if(flag2) {
        accel = 0;
        brake = 1;
    }
    // if(tested == ROAD)   cout << "tested = ROAD " << tested << endl;
    if(tested == ROAD)  road_or_dirt = "ROAD";
    // if(tested == DIRT)   cout << "tested = DIRT " << tested << endl;
    if(tested == DIRT)  road_or_dirt = "DIRT";

    return CarControl(accel, brake, gear, steer, clutch, focus, meta);
}
