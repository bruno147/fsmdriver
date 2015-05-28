#include "Stuck.h"

float Stuck::STUCK_SPEED = 5;
unsigned int Stuck::MIN_RACED_DISTANCE = 100;
unsigned int Stuck::MAX_STUCK_TICKS = 300;
unsigned int Stuck::MAX_SLOW_SPEED_TICKS = 50;

unsigned int Stuck::slowSpeedTicks = 0;
float Stuck::trackInitialPos = 0;

Stuck::Stuck() : elapsedTicks(0) {}

Stuck::Stuck(Stuck const &) {}

Stuck *Stuck::instance() {
    static Stuck instance;
    return &instance;
}

void Stuck::enter(FSMDriver3 *driver, CarState &cs) {
    cout << "Enter Stuck" << endl;
    elapsedTicks = 0;

}

void Stuck::exit(FSMDriver3 *driver) {
    cout << "Exit Stuck" << endl;
}


CarControl Stuck::drive(FSMDriver3 *fsmdriver3, CarState &cs) {
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

float Stuck::getSteer(float trackInitialPos, CarState &cs){
    //return (trackInitialPos > 0 ? 1 : -1);
    if(abs(cs.getAngle()) > 1.557){// around 180 graus
    	return (trackInitialPos > 0 ? -1 : 1);
    }else{
    	return (trackInitialPos > 0 ? 1 : -1);
    }
    
}

float Stuck::getInitialPos(CarState &cs){
	return (trackInitialPos==0?cs.getTrackPos():trackInitialPos);
}

Stuck::~Stuck() {}
