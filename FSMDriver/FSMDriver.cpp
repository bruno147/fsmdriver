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

/**The varience describe the track curvature, information used to choose the state that will control the car.*/
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

/**
*FSMDriver Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.  
*/
FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(StraightLine::instance());
}
/**FSMDriver Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver can be used together with Genetic Algorithm using this function.
*/
FSMDriver::FSMDriver(int argc, char** argv) : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(StraightLine::instance());
    

    LOW_GEAR_LIMIT = 4;
    LOW_RPM = 1500;
    AVERAGE_RPM = 4000;
    HIGH_RPM = 9500;
    STUCK_SPEED = 5;
    MIN_RACED_DISTANCE = 100;
    MAX_STUCK_TICKS = 300;
    MAX_SLOW_SPEED_TICKS = 50;
    MAX_STEERING = 0.12;
    TARGET_POS = 0.7;
    BASE_SPEED = 80;
    MAX_SKIDDING = 3;
    NEGATIVE_ACCEL_PERCENT = 0.1;
    VELOCITY_GEAR_4 = 90;
    VELOCITY_GEAR_3 = 70;
    VELOCITY_GEAR_2 = 40;
    MAX_RETURN_ANGLE = 0.7;
    MIN_RETURN_ANGLE = 0.5;
    MAX_STRAIGHT_LINE_VAR = 1000;
    MIN_STRAIGHT_LINE_VAR = 500;
    MAX_APPROACHING_CURVE_VAR = 400;
    MIN_APPROACHING_CURVE_VAR = 300;

/*    LOW_GEAR_LIMIT = binToFloat(getArgument(0, argv));
    LOW_RPM = binToFloat(getArgument(1, argv));
    AVERAGE_RPM = binToFloat(getArgument(2, argv));
    HIGH_RPM = binToFloat(getArgument(3, argv));

    STUCK_SPEED = binToFloat(getArgument(4, argv));
    MIN_RACED_DISTANCE = binToFloat(getArgument(5, argv));
    MAX_STUCK_TICKS = binToFloat(getArgument(6, argv));
    MAX_SLOW_SPEED_TICKS = binToFloat(getArgument(7, argv));

    MAX_STEERING = binToFloat(getArgument(8, argv));
    TARGET_POS = binToFloat(getArgument(9, argv));
    BASE_SPEED =  binToFloat(getArgument(10, argv));

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
    MIN_APPROACHING_CURVE_VAR =  binToFloat(getArgument(21, argv));*/

    //cout << argc << endl << "kill " << argv[2] << endl;
    // segment_id = stoi(argv[2]);

}
/**This Function is needed to use the Loiacolo files at src.*/
CarControl FSMDriver::wDrive(CarState cs) {
    transition(cs);
    Log::instance()->updateLog(current_state, cs);
    return update(cs);
}
/**This Function is needed to use the Loiacolo files at src.*/
void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}
/**getArgument is used to obtain the driver's paramenters*/
string FSMDriver::getArgument(int i, char** argv){
    return string(argv[1]).substr((i*32), ((i+1)*32));
}
/**This Function is needed to use the Loiacolo files at src.*/
void FSMDriver::onShutdown() {
    Log::instance()->saveTotalTime(segment_id);
    cout << "End of race!" << endl;
}
/**This Function is needed to use the Loiacolo files at src.*/
void FSMDriver::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i] = i*10-90; // @todo como assim?
}
/**The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
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
/**This function is used to turn the string of bits in a float representation of the parameters.*/
float FSMDriver::binToFloat (string bits) {
    bitset<32> a (bits);
    float *value = reinterpret_cast<float*>(&a);

    return *value;
}
/**This function is used to turn the string of bits in a unsigned int representation of the parameters.*/
unsigned int FSMDriver::binToUsignedInt (string bits) {
    bitset<32> a (bits);
    unsigned int *value = reinterpret_cast<unsigned int*>(&a);

    return *value;
}
