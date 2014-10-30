#include "FSMDriver.h"

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

//-------------------------------------------------------------------------------------------------------------------
//FSMDriver Class

FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(StraightLine::instance());
}

CarControl FSMDriver::wDrive(CarState cs) {
    this->transition(cs);
    return update(cs);
}

void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver::onShutdown() {
    cout << "End of race!" << endl;
}

void FSMDriver::init(float *angles){
    for (int i = 0; i < 19; ++i)
        angles[i]=-90+i*10;
}

void iterate_Stuck(CarState & cs){
    if(abs(cs.getSpeedX()<5)&&(cs.getDistRaced()>100)){
        stuck_Counter++;
    }else{
        stuck_Counter = 0;
    }
}

void reset_Stuck_Counters(){
    in_Stuck_Counter = 0;
    stuck_Counter = 0;
}

float variance(CarState &cs) {
    float sensors[19];
    float sensors_mean = 0.;
    float sensorsVariance = 0.;

    for (int i = 0; i < 19; i++) {
        sensors[i] = cs.getTrack(i);
        sensors_mean += sensors[i];
    }

    sensors_mean /= 19.;

    for (int i = 0; i < 19; i++) {
        sensorsVariance += pow((sensors[i] - sensors_mean), 2);
    }

    sensorsVariance /= 19.;

    return sensorsVariance;
}

void FSMDriver::transition(CarState &cs) {
    float sensorsVariance = variance(cs);

    if(stuck_Counter > STUCK_TICKS){
        if (current_state != Stuck::instance()) {
            change_to(Stuck::instance());
        }
        // @todo global counter to run stuck state for a defined time
        if((cs.getTrackPos()>1)&&((cs.getAngle()>0))){
            reset_Stuck_Counters();
        }
        if((cs.getTrackPos()<-1)&&((cs.getAngle()<0))){
            reset_Stuck_Counters();
        }
        if(abs(cs.getTrackPos())<1){
            if((cs.getTrackPos()<0)&&(cs.getAngle()<0)){
                reset_Stuck_Counters();
            }
            if((cs.getTrackPos()>0)&&(cs.getAngle()>0)){
                reset_Stuck_Counters();
            }
        }
        if(++in_Stuck_Counter == 300){
            reset_Stuck_Counters();
        }
    } else if(sensorsVariance > 0.) {
        // Getting track information from the sensor at +5 degrees towards the car axis
        // float rSensor = cs.getTrack(10);
        // Getting track information from the sensor parallel to the car axis
        // float cSensor = cs.getTrack(9);
        // Getting track information from the sensor at -5 degrees towards the car axis
        // float lSensor = cs.getTrack(8);
        // Characteristics of a 'straight' to the FSM:
        //      - If the central sensor is beyond the distance of maximum speed or if it
        //      the biggest of {central, right (+5 degrees), left (-5 degrees)} sensors
        if (sensorsVariance > 1000.) {
            if (current_state != StraightLine::instance()) {
                change_to(StraightLine::instance());
            }
        }
        
        // Characteristics of an 'approaching curve' to the FSM
        // @todo change variable absolute values to exchangeable names
        else if (sensorsVariance > 500. && sensorsVariance < 1000.) {
            if (current_state != ApproachingCurve::instance()) {
                change_to(ApproachingCurve::instance());
            }
        }
        // Characteristics of a 'curve' to the FSM
        else {
            if (current_state != Curve::instance()) {
                change_to(Curve::instance());
            }
        }
    }
    // Characteristics of 'outside of track' states
    else {
        if (current_state != OutOfTrack::instance()) {
            change_to(OutOfTrack::instance());
        }
    }
    iterate_Stuck(cs);
}
