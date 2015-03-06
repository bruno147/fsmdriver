#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "Log.h"

#include <vector>

//Define constants for transition method:
/*
int   FSMDriver::MAX_STRAIGHT_LINE_VAR     = 1000;
int   FSMDriver::MIN_STRAIGHT_LINE_VAR     =  500;
int   FSMDriver::MAX_APPROACHING_CURVE_VAR =  400;
int   FSMDriver::MIN_APPROACHING_CURVE_VAR =  300;
*/


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

FSMDriver::FSMDriver(int argc, char** argv) : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(StraightLine::instance());
    

    for (int i = 0; i < 22; i++) {
        parameters[i] = binToFloat (string(argv[1]).substr((i*32), ((i+1)*32)));
        //cout << "Parameter #" << i << ":" << parameters[i] << endl; // Optional output command
    }
    LOW_GEAR_LIMIT = parameters[0];
    LOW_RPM = parameters[1];
    AVERAGE_RPM = parameters[2];
    HIGH_RPM = parameters[3];

    STUCK_SPEED = parameters[4];
    MIN_RACED_DISTANCE = parameters[5];
    MAX_STUCK_TICKS = parameters[6];
    MAX_SLOW_SPEED_TICKS = parameters[7];

    MAX_STEERING = parameters[8];
    TARGET_POS = parameters[9];
    BASE_SPEED = parameters[10];

    MAX_SKIDDING = parameters[11];
    NEGATIVE_ACCEL_PERCENT = parameters[12];
    VELOCITY_GEAR_4 = parameters[13];
    VELOCITY_GEAR_3 = parameters[14];
    VELOCITY_GEAR_2 = parameters[15];
    MAX_RETURN_ANGLE =parameters[16];
    MIN_RETURN_ANGLE = parameters[17];

    MAX_STRAIGHT_LINE_VAR = parameters[18];
    MIN_STRAIGHT_LINE_VAR = parameters[19];
    MAX_APPROACHING_CURVE_VAR = parameters[20];
    MIN_APPROACHING_CURVE_VAR = parameters[21];

    //cout << argc << endl << "kill " << argv[2] << endl;
    segment_id = stoi(argv[2]);

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
    Log::instance()->saveTotalTime(segment_id);
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

float FSMDriver::binToFloat (string bits) {
    bitset<32> a (bits);
    float *value = reinterpret_cast<float*>(&a);

    return *value;
}