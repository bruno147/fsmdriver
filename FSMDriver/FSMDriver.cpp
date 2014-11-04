#include "FSMDriver.h"

#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"

//Define constants for transition method:
const float FSMDriver::LEFT_EDGE        =-0.8;
const float FSMDriver::RIGHT_EDGE       =1;
const float FSMDriver::MAX_SPEED_DIST   =  20.0;
const float FSMDriver::MAX_STR_ANGLE    =0.3;
const float FSMDriver::MIN_STR_ANGLE    =-0.3;
const int FSMDriver::STUCK_TICKS        =110;
//Global variable to count the tics in stuck mode
int stuck_Counter   =   0;
int in_Stuck_Counter    =0;

const int NUM_SENSORS = 19;
const int MIN_RACED_DISTANCE = 100;
const int MAX_STUCK_TICKS = 300;
const float STUCK_SPEED = 5;




/***********************
 * Auxiliary functions *
 ***********************/

inline bool seemsStuck(CarState &cs) {
    return (abs(cs.getSpeedX()) <= STUCK_SPEED);
}

inline bool justStartedRace(CarState &cs) {
    return (cs.getDistRaced() <= MIN_RACED_DISTANCE); 
}

inline bool isStuck(CarState &cs) {
    return (seemsStuck(cs) && !justStartedRace(cs));
}

inline void iterateStuck(CarState &cs) {
    if(isStuck(cs)) ++stuck_Counter;
    else stuck_Counter = 0;
}

inline void resetStuckCounters(){
    in_Stuck_Counter = 0;
    stuck_Counter = 0;
}

float variance(CarState &cs) {
    float sensors[NUM_SENSORS];
    float mean = 0;
    float var = 0;

    for (int i = 0; i < NUM_SENSORS; ++i) {
        sensors[i] = cs.getTrack(i);
        mean += sensors[i];
    }

    mean /= NUM_SENSORS;

    for (int i = 0; i < NUM_SENSORS; ++i)
        var += (sensors[i] - mean)*(sensors[i] - mean);

    var /= NUM_SENSORS;

    return var;
}

inline bool outOfTrackLeft(float trackPos, float angle) {
    return ((trackPos > 1) && (angle > 0));
}

inline bool outOfTrackRight(float trackPos, float angle) {
    return ((trackPos < -1) && (angle < 0));
}

inline bool outOfTrack(float trackPos, float angle) {
    return (outOfTrackLeft(trackPos, angle) || outOfTrackRight(trackPos, angle));
}

inline bool onTrack(float trackPos, float angle) {
    return (((trackPos < 0) && (angle < 0)) ||
            ((trackPos > -1) && (trackPos < 0) && (angle < 0)) ||
            ((trackPos > 0) && (trackPos < 1) && (angle > 0)));
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
    this->cs = cs;
    DrivingState<FSMDriver> *state = current_state;

    float sensorsVariance = variance(cs);
    iterateStuck(cs);
    if(stuck_Counter > STUCK_TICKS) {
        state = Stuck::instance();

        float angle = cs.getAngle();
        float trackPos = cs.getTrackPos();

        // @todo global counter to run stuck state for a defined time
        if(outOfTrack(trackPos, angle) || onTrack(trackPos, angle))
            resetStuckCounters();

        ++in_Stuck_Counter;

        if(in_Stuck_Counter >= MAX_STUCK_TICKS) resetStuckCounters();
    } else if(sensorsVariance > 0) {
        if (sensorsVariance > 1000) state = StraightLine::instance();
        // @todo change variable absolute values to exchangeable names
        else if (sensorsVariance > 500 && sensorsVariance < 1000)
            state = ApproachingCurve::instance();
        else
            state = Curve::instance();
    } else
        state = OutOfTrack::instance();

    if (current_state != state) change_to(state);
}