/**  @file: FSMDriver3.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "FSMDriver3.h"
#include <vector>



/******************************************************************************/
#define NUM_SENSORS 19
/******************************************************************************/

int signum(float n) {
    if (n < 0) return -1;
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//FSMDriver3 Class

/**
*FSMDriver3 Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.
*/
FSMDriver3::FSMDriver3() {
    changeTo(&inside_track);
}

void
FSMDriver3::onRestart() {
    cout << "Restarting the race!" << endl;
}

void
FSMDriver3::onShutdown() {
    cout << "End of race!" << endl;
}

void
FSMDriver3::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i]=signum((i*1.0/3)-3)*exp(-(0.5)*powf((((i+9)%18)*1.0/3)-3, 2))*90;
}
/**The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
void
FSMDriver3::transition(CarState &cs) {
    DrivingState *state = current_state;

    if(stuck.isStuck(cs)) {
        state = &stuck;
    } else {
        if (cs.getTrack(1) > 0)
            state = &inside_track;
        else
            state = &out_of_track;
    }

    if (current_state != state) changeTo(state);
}

FSMDriver3::~FSMDriver3() {
    /* Nothing */
}
