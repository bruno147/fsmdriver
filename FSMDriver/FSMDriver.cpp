#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>

//Define constants for transition method:
const float FSMDriver::LEFT_EDGE        =-0.8;
const float FSMDriver::RIGHT_EDGE       =1;
const float FSMDriver::MAX_SPEED_DIST   =  20.0;
const float FSMDriver::MAX_STR_ANGLE    =0.3;
const float FSMDriver::MIN_STR_ANGLE    =-0.3;

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
    return update(cs);
}

void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver::onShutdown() {
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
        if (var > 1000) 
			state = StraightLine::instance();
        else if (var > 500) /* @todo change this value (or previous) to something that works - race start is too slow. And in a straight line, should *not* enter this state... */
            state = ApproachingCurve::instance();
        else if(var > 0)
            state = Curve::instance();
	    else
	        state = OutOfTrack::instance();
	}

    if (current_state != state) change_to(state);
}