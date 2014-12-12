#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>
#include <fstream>
#include <string>

#define NUM_SENSORS 19
#define NUM_PARAMETERS 22


//Parameters used in genetic algorithm with their respective original values
//*****************************************************************************

    float StraightLine::LOW_GEAR_LIMIT = 4;
    float StraightLine::LOW_RPM = 1500;
    float StraightLine::AVERAGE_RPM = 4000;
    float StraightLine::HIGH_RPM = 9500;

    float Stuck::STUCK_SPEED = 5;
    float Stuck::MIN_RACED_DISTANCE = 100;
    float Stuck::MAX_STUCK_TICKS = 300;
    float Stuck::MAX_SLOW_SPEED_TICKS = 50;

    float ApproachingCurve::MAX_STEERING = 0.12;
    float ApproachingCurve::TARGET_POS = 0.7;
    float ApproachingCurve::BASE_SPEED = 80;

    float OutOfTrack::MAX_SKIDDING = 3;
    float OutOfTrack::NEGATIVE_ACCEL_PERCENT = 0.1;
    float OutOfTrack::VELOCITY_GEAR_4 = 90;
    float OutOfTrack::VELOCITY_GEAR_3 = 70;
    float OutOfTrack::VELOCITY_GEAR_2 = 40;
    float OutOfTrack::MAX_RETURN_ANGLE = 0.7;
    float OutOfTrack::MIN_RETURN_ANGLE = 0.5;

    float FSMDriver::MAX_STRAIGHT_LINE_VAR     = 1000;
    float FSMDriver::MIN_STRAIGHT_LINE_VAR     =  500;
    float FSMDriver::MAX_APPROACHING_CURVE_VAR =  400;
    float FSMDriver::MIN_APPROACHING_CURVE_VAR =  300;

//*****************************************************************************

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
bool FSMDriver::loadParameters(float* parameters, string filename) {
    fstream fs;
    string aux;
    fs.open(filename);
    if (fs.good()) {
        for (int i = 0; i < NUM_PARAMETERS; i++) {
            fs >> aux;
            parameters[i] = stof(aux);
        }
        fs.close();
        return 1;
    }
    else
        return 0;
}

FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    float parameters[NUM_PARAMETERS];
    if (loadParameters(parameters, "teste.txt")) {

        StraightLine::LOW_GEAR_LIMIT = parameters[0];
        StraightLine::LOW_RPM = parameters[1];
        StraightLine::AVERAGE_RPM = parameters[2];
        StraightLine::HIGH_RPM = parameters[3];

        Stuck::STUCK_SPEED = parameters[4];
        Stuck::MIN_RACED_DISTANCE = parameters[5];
        Stuck::MAX_STUCK_TICKS = parameters[6];
        Stuck::MAX_SLOW_SPEED_TICKS = parameters[7];

        ApproachingCurve::MAX_STEERING = parameters[8];
        ApproachingCurve::TARGET_POS = parameters[9];
        ApproachingCurve::BASE_SPEED = parameters[10];

        OutOfTrack::MAX_SKIDDING = parameters[11];
        OutOfTrack::NEGATIVE_ACCEL_PERCENT = parameters[12];
        OutOfTrack::VELOCITY_GEAR_4 = parameters[13];
        OutOfTrack::VELOCITY_GEAR_3 = parameters[14];
        OutOfTrack::VELOCITY_GEAR_2 = parameters[15];
        OutOfTrack::MAX_RETURN_ANGLE =parameters[16];
        OutOfTrack::MIN_RETURN_ANGLE = parameters[17];

        FSMDriver::MAX_STRAIGHT_LINE_VAR     = parameters[18];
        FSMDriver::MIN_STRAIGHT_LINE_VAR     =  parameters[19];
        FSMDriver::MAX_APPROACHING_CURVE_VAR =  parameters[20];
        FSMDriver::MIN_APPROACHING_CURVE_VAR =  parameters[21];
    }

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