#include "Stuck.h"

float Stuck::STUCK_SPEED = 5;
unsigned int Stuck::MIN_RACED_DISTANCE = 100;
unsigned int Stuck::MAX_STUCK_TICKS = 300;
unsigned int Stuck::MAX_SLOW_SPEED_TICKS = 50;

unsigned int Stuck::slowSpeedTicks = 0;
float Stuck::trackInitialPos = 0;

Stuck::Stuck(FSMDriver *o, float _ss, int _mrd, int _mst, int _msst)
            : DrivingState(o) {
    STUCK_SPEED = _ss;
    MIN_RACED_DISTANCE  = _mrd;
    MAX_STUCK_TICKS = _mst;
    MAX_SLOW_SPEED_TICKS = _msst;
    elapsedTicks = 0;
}

// Stuck::Stuck(Stuck const &) {}

void Stuck::setParameters(float _ss = 0, int _mrd = 0, int _mst = 0, int _msst = 0) {
    STUCK_SPEED = _ss;
    MIN_RACED_DISTANCE  = _mrd;
    MAX_STUCK_TICKS = _mst;
    MAX_SLOW_SPEED_TICKS = _msst;
}


CarControl Stuck::drive(    CarState &cs) {
    ++elapsedTicks;
    trackInitialPos = getInitialPos(cs);
    if(notStuckAnymore(cs.getTrackPos(), cs.getAngle()) || hasBeenStuckLongEnough()){
        elapsedTicks = 0;
        slowSpeedTicks = 0;
        trackInitialPos = 0;
    }
    const float accel = 1, brake = 0, clutch = 0;
    const int gear = -1, focus = 0, meta = 0;
    float steer = getSteer(trackInitialPos, cs);

    return CarControl(accel, brake, gear, steer, clutch, focus, meta);
}

bool Stuck::justStartedRace(CarState &cs) {
    return (cs.getDistRaced() <= MIN_RACED_DISTANCE);
}

bool Stuck::onRightWay(float trackPos, float angle) {
    return (((trackPos < 0) && (angle > -1.57) && (angle < 0)) ||
            ((trackPos > 0) && (angle < 1.57 ) && (angle > 0)) ||
            ((trackPos > 1) && (angle > 0))||
            ((trackPos < -1) && (angle < 0)));
}

/* @todo give this test (and the previous ones) with a meaningful name... */
bool Stuck::notStuckAnymore(float trackPos, float angle) {
    return (onRightWay(trackPos, angle));
}

bool Stuck::hasBeenStuckLongEnough() {
    return (elapsedTicks >= MAX_STUCK_TICKS);
}

bool Stuck::isStuck(CarState &cs) {
    return (seemsStuck(cs) && !justStartedRace(cs));
}

float Stuck::getSteer(float trackInitialPos, CarState &cs){
    //return (trackInitialPos > 0 ? 1 : -1);
    if(abs(cs.getAngle()) > 1.557){// around 180 graus
        return (trackInitialPos > 0 ? -1 : 1);
    }else{
    	return (trackInitialPos > 0 ? 1 : -1);
    }
}

bool Stuck::seemsStuck(CarState &cs) {
    cs.getSpeedX()<STUCK_SPEED?slowSpeedTicks++:slowSpeedTicks = 0;
    if(notStuckAnymore(cs.getTrackPos(), cs.getAngle())){
        slowSpeedTicks=0;
    }
    return (slowSpeedTicks>MAX_SLOW_SPEED_TICKS?1:0);
}

float Stuck::getInitialPos(CarState &cs){
	return (trackInitialPos==0?cs.getTrackPos():trackInitialPos);
}

Stuck::~Stuck() {}
