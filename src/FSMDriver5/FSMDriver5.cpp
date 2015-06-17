#include "FSMDriver5.h"

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
// FSMDriver5 Class

/** FSMDriver5 Constructor: it initilize at straight_line state in the begining of the race, here the parameters are set with fixed values.
*/
FSMDriver5::FSMDriver5() {
    changeTo(&straight_line);
}

/** FSMDriver5 Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver5 can be used together with Genetic Algorithm using this function.
*/
FSMDriver5::FSMDriver5(int argc, char** argv) {

    // low_gear_limit = 4;
    // low_rpm = 1500;
    // average_rpm = 4000;
    // high_rpm = 9500;
    // stuck_speed = 5;
    // minimum_distance_raced = 100;
    // maximum_number_of_ticks_stuck = 300;
    // maximum_number_of_ticks_in_slow_speed = 50;
    // max_steering = 0.12;
    // target_pos = 0.7;
    // base_speed = 80;
    // max_skidding = 3;
    // negative_accel_percent = 0.1;
    // velocity_gear_4 = 90;
    // velocity_gear_3 = 70;
    // velocity_gear_2 = 40;
    // max_return_angle = 0.7;
    // min_return_angle = 0.5;
    // MAX_straight_line_var = 1000;
    // min_straight_line_var = 500;
    // max_approaching_curve_var = 400;
    // min_approaching_curve_var = 300;

    float low_gear_limit = binToFloat(getArgument(0, argv));
    float low_rpm = binToFloat(getArgument(1, argv));
    float average_rpm = binToFloat(getArgument(2, argv));
    float high_rpm = binToFloat(getArgument(3, argv));

    float stuck_speed = binToFloat(getArgument(4, argv));
    float minimum_distance_raced = binToFloat(getArgument(5, argv));
    float maximum_number_of_ticks_stuck = binToFloat(getArgument(6, argv));
    float maximum_number_of_ticks_in_slow_speed = binToFloat(getArgument(7, argv));

    float max_steering = binToFloat(getArgument(8, argv));
    float target_pos = binToFloat(getArgument(9, argv));
    float base_speed =  binToFloat(getArgument(10, argv));

    float max_skidding =  binToFloat(getArgument(11, argv));
    float negative_accel_percent =  binToFloat(getArgument(12, argv));
    float velocity_gear_4 =  binToFloat(getArgument(13, argv));
    float velocity_gear_3 =  binToFloat(getArgument(14, argv));
    float velocity_gear_2 =  binToFloat(getArgument(15, argv));
    float max_return_angle = binToFloat(getArgument(16, argv));
    float min_return_angle =  binToFloat(getArgument(17, argv));

    max_straight_line_var =  binToFloat(getArgument(18, argv));
    min_straight_line_var =  binToFloat(getArgument(19, argv));
    max_approaching_curve_var =  binToFloat(getArgument(20, argv));
    min_approaching_curve_var =  binToFloat(getArgument(21, argv));

    //cout << argc << endl << "kill " << argv[2] << endl;
    segment_id = stoi(argv[2]);

    straight_line.low_gear_limit = low_gear_limit;
    straight_line.low_rpm = low_rpm;
    straight_line.average_rpm = average_rpm;
    straight_line.high_rpm = high_rpm;

    approaching_curve.max_steering = max_steering;
    approaching_curve.target_pos = target_pos;
    approaching_curve.base_speed = base_speed;

    out_of_track.max_skidding = max_skidding;
    out_of_track.negative_accel_percent = negative_accel_percent;
    out_of_track.velocity_gear_4 = velocity_gear_4;
    out_of_track.velocity_gear_3 = velocity_gear_3;
    out_of_track.velocity_gear_2 = velocity_gear_2;
    out_of_track.max_return_angle = max_return_angle;
    out_of_track.min_return_angle = min_return_angle;

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
/** The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
void FSMDriver5::transition(CarState &cs) {
    DrivingState *state = current_state;

    if(stuck.isStuck(cs)) {
        state = &stuck;
    } else {
        float var = trackReadingsVariance(cs);

        /* @todo change numbers to constants with meaningful names. */
        if (var > max_straight_line_var || ((var > min_straight_line_var) && current_state == &straight_line))
            state = &straight_line;
        else if ((var > max_approaching_curve_var && current_state != &curve)
         || ((var > min_approaching_curve_var) && current_state == &approaching_curve)) /* @todo change this value (or previous) to something that works - race start is too slow. And in a straight line, should *not* enter this state... */
            state = &approaching_curve;
        else if(var > 0)
            state = &curve;
        else
            state = &out_of_track;
    }

    if (current_state != state) changeTo(state);

    Log::instance()->updateLog(current_state, cs);
}
/** This function is used to turn the string of bits in a float representation of the parameters.*/
float FSMDriver5::binToFloat (string bits) {
    bitset<32> a (bits);
    float *value = reinterpret_cast<float*>(&a);

    return *value;
}
/** This function is used to turn the string of bits in a unsigned int representation of the parameters.*/
unsigned int FSMDriver5::binToUsignedInt (string bits) {
    bitset<32> a (bits);
    unsigned int *value = reinterpret_cast<unsigned int*>(&a);

    return *value;
}

FSMDriver5::~FSMDriver5() {
}
