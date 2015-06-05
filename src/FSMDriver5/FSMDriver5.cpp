#include "FSMDriver5.h"

//Define constants for transition method:
/*
int   FSMDriver5::MAX_STRAIGHT_LINE_VAR     = 1000;
int   FSMDriver5::MIN_STRAIGHT_LINE_VAR     =  500;
int   FSMDriver5::MAX_APPROACHING_CURVE_VAR =  400;
int   FSMDriver5::MIN_APPROACHING_CURVE_VAR =  300;
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
//FSMDriver5 Class

/**
<<<<<<< HEAD:FSMDriver55/FSMDriver55.cpp
*FSMDriver5 Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.
=======
*FSMDriver55 Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.
>>>>>>> refactoring:src/FSMDriver55/FSMDriver55.cpp
*/
FSMDriver5::FSMDriver5() : straightLine(this), approachingCurve(this), curve(this), outOfTrack(this), stuck(this) {
    change_to(&straightLine);
}
/**FSMDriver5 Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver5 can be used together with Genetic Algorithm using this function.
*/
FSMDriver5::FSMDriver5(int argc, char** argv) : straightLine(this), approachingCurve(this), curve(this), outOfTrack(this), stuck(this) {


    // LOW_GEAR_LIMIT = 4;
    // LOW_RPM = 1500;
    // AVERAGE_RPM = 4000;
    // HIGH_RPM = 9500;
    // stuck_speed = 5;
    // minimum_distance_raced = 100;
    // maximum_number_of_ticks_stuck = 300;
    // maximum_number_of_ticks_in_slow_speed = 50;
    // MAX_STEERING = 0.12;
    // TARGET_POS = 0.7;
    // BASE_SPEED = 80;
    // MAX_SKIDDING = 3;
    // NEGATIVE_ACCEL_PERCENT = 0.1;
    // VELOCITY_GEAR_4 = 90;
    // VELOCITY_GEAR_3 = 70;
    // VELOCITY_GEAR_2 = 40;
    // MAX_RETURN_ANGLE = 0.7;
    // MIN_RETURN_ANGLE = 0.5;
    // MAX_STRAIGHT_LINE_VAR = 1000;
    // MIN_STRAIGHT_LINE_VAR = 500;
    // MAX_APPROACHING_CURVE_VAR = 400;
    // MIN_APPROACHING_CURVE_VAR = 300;

    float LOW_GEAR_LIMIT = binToFloat(getArgument(0, argv));
    float LOW_RPM = binToFloat(getArgument(1, argv));
    float AVERAGE_RPM = binToFloat(getArgument(2, argv));
    float HIGH_RPM = binToFloat(getArgument(3, argv));

    float stuck_speed = binToFloat(getArgument(4, argv));
    float minimum_distance_raced = binToFloat(getArgument(5, argv));
    float maximum_number_of_ticks_stuck = binToFloat(getArgument(6, argv));
    float maximum_number_of_ticks_in_slow_speed = binToFloat(getArgument(7, argv));

    float MAX_STEERING = binToFloat(getArgument(8, argv));
    float TARGET_POS = binToFloat(getArgument(9, argv));
    float BASE_SPEED =  binToFloat(getArgument(10, argv));

    float MAX_SKIDDING =  binToFloat(getArgument(11, argv));
    float NEGATIVE_ACCEL_PERCENT =  binToFloat(getArgument(12, argv));
    float VELOCITY_GEAR_4 =  binToFloat(getArgument(13, argv));
    float VELOCITY_GEAR_3 =  binToFloat(getArgument(14, argv));
    float VELOCITY_GEAR_2 =  binToFloat(getArgument(15, argv));
    float MAX_RETURN_ANGLE = binToFloat(getArgument(16, argv));
    float MIN_RETURN_ANGLE =  binToFloat(getArgument(17, argv));

    MAX_STRAIGHT_LINE_VAR =  binToFloat(getArgument(18, argv));
    MIN_STRAIGHT_LINE_VAR =  binToFloat(getArgument(19, argv));
    MAX_APPROACHING_CURVE_VAR =  binToFloat(getArgument(20, argv));
    MIN_APPROACHING_CURVE_VAR =  binToFloat(getArgument(21, argv));

    //cout << argc << endl << "kill " << argv[2] << endl;
    segment_id = stoi(argv[2]);

    straightLine.LOW_GEAR_LIMIT = LOW_GEAR_LIMIT;
    straightLine.LOW_RPM = LOW_RPM;
    straightLine.AVERAGE_RPM = AVERAGE_RPM;
    straightLine.HIGH_RPM = HIGH_RPM;

    approachingCurve.MAX_STEERING = MAX_STEERING;
    approachingCurve.TARGET_POS = TARGET_POS;
    approachingCurve.BASE_SPEED = BASE_SPEED;

    outOfTrack.MAX_SKIDDING = MAX_SKIDDING;
    outOfTrack.NEGATIVE_ACCEL_PERCENT = NEGATIVE_ACCEL_PERCENT;
    outOfTrack.VELOCITY_GEAR_4 = VELOCITY_GEAR_4;
    outOfTrack.VELOCITY_GEAR_3 = VELOCITY_GEAR_3;
    outOfTrack.VELOCITY_GEAR_2 = VELOCITY_GEAR_2;
    outOfTrack.MAX_RETURN_ANGLE = MAX_RETURN_ANGLE;
    outOfTrack.MIN_RETURN_ANGLE = MIN_RETURN_ANGLE;

    stuck.stuck_speed = stuck_speed;
    stuck.minimum_distance_raced = minimum_distance_raced;
    stuck.maximum_number_of_ticks_stuck = maximum_number_of_ticks_stuck;
    stuck.maximum_number_of_ticks_in_slow_speed = maximum_number_of_ticks_in_slow_speed;
}

void FSMDriver5::onRestart() {
    cout << "Restarting the race!" << endl;
}
string FSMDriver5::getArgument(int i, char** argv){
    return string(argv[1]).substr((i*32), ((i+1)*32));
}
void FSMDriver5::onShutdown() {
    Log::instance()->saveTotalTime(segment_id);
    cout << "End of race!" << endl;
}
void FSMDriver5::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i] = i*10-90; // @todo como assim?
}
/**The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
void FSMDriver5::transition(CarState &cs) {
    DrivingState *state = current_state;

    if(stuck.isStuck(cs)) {
        state = &stuck;
    } else {
        float var = trackReadingsVariance(cs);

        /* @todo change numbers to constants with meaningful names. */
        if (var > MAX_STRAIGHT_LINE_VAR || ((var>MIN_STRAIGHT_LINE_VAR) && current_state == &straightLine))
            state = &straightLine;
        else if ((var > MAX_APPROACHING_CURVE_VAR && current_state != &curve)
         || ((var > MIN_APPROACHING_CURVE_VAR) && current_state == &approachingCurve)) /* @todo change this value (or previous) to something that works - race start is too slow. And in a straight line, should *not* enter this state... */
            state = &approachingCurve;
        else if(var > 0)
            state = &curve;
        else
            state = &outOfTrack;
    }

    if (current_state != state) change_to(state);

    Log::instance()->updateLog(current_state, cs);
}
/**This function is used to turn the string of bits in a float representation of the parameters.*/
float FSMDriver5::binToFloat (string bits) {
    bitset<32> a (bits);
    float *value = reinterpret_cast<float*>(&a);

    return *value;
}
/**This function is used to turn the string of bits in a unsigned int representation of the parameters.*/
unsigned int FSMDriver5::binToUsignedInt (string bits) {
    bitset<32> a (bits);
    unsigned int *value = reinterpret_cast<unsigned int*>(&a);

    return *value;
}

FSMDriver5::~FSMDriver5() {
}
