#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "Log.h"

#include <vector>

//Define constants for transition method:

const int   FSMDriver::MAX_STRAIGHT_LINE_VAR     = 1000;
const int   FSMDriver::MIN_STRAIGHT_LINE_VAR     =  500;
const int   FSMDriver::MAX_APPROACHING_CURVE_VAR =  400;
const int   FSMDriver::MIN_APPROACHING_CURVE_VAR =  300;

/******************************************************************************/
const int NUM_SENSORS = 19;
/******************************************************************************/


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
//FSMDriver Class


FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(StraightLine::instance());
}

CarControl FSMDriver::wDrive(CarState cs) {
    transition(cs);
    Log::instance()->updateLog(current_state, cs);
    return update(cs);
}

void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver::onShutdown() {
    Log::instance()->saveTotalTime();
    cout << "End of race!" << endl;
}

void FSMDriver::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i] = i*10-90; // @todo como assim?
}

void FSMDriver::transition(CarState &cs) {
    DrivingState<FSMDriver> *state = current_state;

    if(Stuck::isStuck(cs)) {
        state = Stuck::instance();
    } else {
        float var = trackReadingsVariance(cs);
        
        /* @todo change numbers to constants with meaningful names. */
        if (var > MAX_STRAIGHT_LINE_VAR || ((var>MIN_STRAIGHT_LINE_VAR) && current_state==StraightLine::instance())) 
            state = StraightLine::instance();
        else if ((var > MAX_APPROACHING_CURVE_VAR && current_state != Curve::instance())
         || ((var > MIN_APPROACHING_CURVE_VAR) && current_state==ApproachingCurve::instance())) /* @todo change this value (or previous) to something that works - race start is too slow. And in a straight line, should *not* enter this state... */
            state = ApproachingCurve::instance();
        else if(var > 0)
            state = Curve::instance();
        else
            state = OutOfTrack::instance();
    }

    if (current_state != state) change_to(state);
}