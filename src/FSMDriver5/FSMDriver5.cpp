/**  @file: FSMDriver5.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "FSMDriver5.h"

/******************************************************************************/
const int NUM_SENSORS = 19;
/******************************************************************************/

/** The varience describe the track curvature, information used to choose the state that will control the car.*/
float trackReadingsVariance(CarState &cs) {
    vector<float> sensors(NUM_SENSORS);
    float mean = 0, var = 0;

    for (int i = 0; i < NUM_SENSORS; ++i) {
        sensors[i] = cs.getTrack(i);
        mean += sensors[i];
    }

    mean /= NUM_SENSORS;

    for(auto sensor : sensors)
        var += (sensor-mean)*(sensor-mean);

    var /= NUM_SENSORS;

    return var;
}


//-------------------------------------------------------------------------------------------------------------------
// FSMDriver5 Class

/** FSMDriver5 Constructor: it initilize at straight_line state in the begining of the race, here the parameters are set with fixed values.
    @see transition()
*/
FSMDriver5::FSMDriver5() {
    changeTo(&straight_line);
}

void
FSMDriver5::onRestart() {
    cout << "Restarting the race!" << endl;
}
void
FSMDriver5::onShutdown() {
    cout << "End of race!" << endl;
}
void
FSMDriver5::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i] = i*10-90;
}
/** The transition choose the most fitted state at the moment of the race. The selection depends of variance of the range finders values. */
void
FSMDriver5::transition(CarState &cs) {
    DrivingState *state = current_state;

    if(stuck.isStuck(cs)) {
        state = &stuck;
    } else {
        float var = trackReadingsVariance(cs);

        /* @todo change numbers to constants with meaningful names. */
        if (var > max_straight_line_var || ((var > min_straight_line_var) && current_state == &straight_line))
            state = &straight_line;
        else if ((var > max_approaching_curve_var && current_state != &curve)
         || ((var > min_approaching_curve_var) && current_state == &approaching_curve))
            state = &approaching_curve;
        else if(var > 0)
            state = &curve;
        else
            state = &out_of_track;
    }

    if (current_state != state) changeTo(state);

}

FSMDriver5::~FSMDriver5() {
}
