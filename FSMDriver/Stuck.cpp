#include "Stuck.h"

unsigned int Stuck::slowSpeedTicks=0;
float Stuck::trackInitialPos=0;

Stuck::Stuck() : elapsedTicks(0) {}

Stuck::Stuck(Stuck const &) {}

Stuck *Stuck::instance() {
    static Stuck instance;
    return &instance;
}

void Stuck::enter(FSMDriver *driver, CarState &cs) {
    cout << "Enter Stuck" << endl;
    elapsedTicks = 0;

}

void Stuck::exit(FSMDriver *driver) {
    cout << "Exit Stuck" << endl;
}

CarControl Stuck::drive(FSMDriver *fsmdriver, CarState &cs) {
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

bool Stuck::seemsStuck(CarState &cs) {
	cs.getSpeedX()<STUCK_SPEED?slowSpeedTicks++:slowSpeedTicks=0;
	if(notStuckAnymore(cs.getTrackPos(), cs.getAngle())){
		slowSpeedTicks=0;
	}
	return (slowSpeedTicks>MAX_SLOW_SPEED_TICKS?1:0);
    //return (abs(cs.getSpeedX()) <= STUCK_SPEED);
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