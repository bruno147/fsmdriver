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
    


    LOW_GEAR_LIMIT = binToFloat(getArgument(0, argv));
    LOW_RPM = binToFloat(getArgument(1, argv));
    AVERAGE_RPM = binToFloat(getArgument(2, argv));
    HIGH_RPM = binToFloat(getArgument(3, argv));

    STUCK_SPEED = binToFloat(getArgument(4, argv));
    MIN_RACED_DISTANCE = binToFloat(getArgument(5, argv));
    MAX_STUCK_TICKS = binToFloat(getArgument(6, argv));
    MAX_SLOW_SPEED_TICKS = binToFloat(getArgument(7, argv));


    //temporary normalization of MAX_STEERING between -1 and 1
    MAX_STEERING = -1+2*normalization(binToUsignedInt(getArgument(8, argv)));

    //temporary normalization of TARGET_POS between -1 and 1
    TARGET_POS = -1+2*normalization(binToUsignedInt(getArgument(9, argv)));

    //temporary normalization of BASE_SPEED between 0 and 340 *just because*
    BASE_SPEED =  340*normalization(binToUsignedInt(getArgument(10, argv)));

    MAX_SKIDDING =  binToFloat(getArgument(11, argv));
    NEGATIVE_ACCEL_PERCENT =  binToFloat(getArgument(12, argv));
    VELOCITY_GEAR_4 =  binToFloat(getArgument(13, argv));
    VELOCITY_GEAR_3 =  binToFloat(getArgument(14, argv));
    VELOCITY_GEAR_2 =  binToFloat(getArgument(15, argv));
    MAX_RETURN_ANGLE = binToFloat(getArgument(16, argv));
    MIN_RETURN_ANGLE =  binToFloat(getArgument(17, argv));

    MAX_STRAIGHT_LINE_VAR =  binToFloat(getArgument(18, argv));
    MIN_STRAIGHT_LINE_VAR =  binToFloat(getArgument(19, argv));
    MAX_APPROACHING_CURVE_VAR =  binToFloat(getArgument(20, argv));
    MIN_APPROACHING_CURVE_VAR =  binToFloat(getArgument(21, argv));

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

unsigned int FSMDriver::binToUsignedInt (string bits) {
    bitset<32> a (bits);
    unsigned int *value = reinterpret_cast<unsigned int*>(&a);

    return *value;
}
string FSMDriver::getArgument(int i, char** argv){
    return string(argv[1]).substr((i*32), ((i+1)*32));
}

float FSMDriver::normalization(unsigned int number){
    return ((float)number/binToUsignedInt("11111111111111111111111111111111"));
}
