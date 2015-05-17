#include <cmath>
#include "Stuck.h"

// unsigned int Stuck::slowSpeedTicks = 0;
// float Stuck::trackInitialPos = 0;

Stuck::Stuck() : elapsedTicks(0) {}

Stuck::Stuck(const Stuck &s) {}

bool Stuck::seemsStuck(CarState &cs) {
    if(cs.getSpeedX() < STUCK_SPEED)
        ++slowSpeedTicks;
    else
        slowSpeedTicks = 0;

    if(notStuckAnymore(cs.getTrackPos(), cs.getAngle()))
        slowSpeedTicks = 0;

    return (slowSpeedTicks > MAX_SLOW_SPEED_TICKS);
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

/** Indicates if the driver is stuck according to its perception of the
 * environment.
 * @param cs Driver's perception of the environment.
 * @return true if the it is stuck, false otherwise. */

bool Stuck::isStuck(CarState &cs) {
    return (seemsStuck(cs) && !justStartedRace(cs));
}

Stuck *Stuck::instance() {
    static Stuck instance;
    return &instance;
}

void Stuck::enter(BaseDriver *driver, CarState &cs) {
    elapsedTicks = 0;
}

/** @todo describe implementation! */
CarControl Stuck::drive(BaseDriver *Driver, CarState &cs) {
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


float Stuck::getSteer(float trackInitialPos, CarState &cs) {
    if(abs(cs.getAngle()) > 1.557){// around 180 graus
	   return (trackInitialPos > 0 ? -1 : 1);
    } else {
	   return (trackInitialPos > 0 ? 1 : -1);
    }
}


float Stuck::getInitialPos(CarState &cs){
	return (trackInitialPos ? trackInitialPos : cs.getTrackPos());
}


Stuck::~Stuck() {}
