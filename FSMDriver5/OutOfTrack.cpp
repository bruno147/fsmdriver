#include "OutOfTrack.h"

float MAX_SKIDDING = 3;
float NEGATIVE_ACCEL_PERCENT = 0.1;
int VELOCITY_GEAR_4 = 90;
int VELOCITY_GEAR_3 = 70;
int VELOCITY_GEAR_2 = 40;
float MAX_RETURN_ANGLE = 0.7;
float MIN_RETURN_ANGLE = 0.5;

OutOfTrack::OutOfTrack() {}

OutOfTrack::OutOfTrack(OutOfTrack const &) {}

OutOfTrack *OutOfTrack::instance() {
    static OutOfTrack instance;
    return &instance;
}

void OutOfTrack::enter(FSMDriver *driver) {
    //cout << "Enter OutOfTrack" << endl;
}

void OutOfTrack::exit(FSMDriver *driver) {
    //cout << "Exit OutOfTrack" << endl;
}

CarControl OutOfTrack::drive(FSMDriver *fsmdriver, CarState &cs) {
    const float clutch = 0;
    const int focus = 0, meta = 0;

    return CarControl(getAccel(cs), getBrake(cs), getGear(cs), getSteer(cs), clutch, focus, meta);
}

float OutOfTrack::getBrake(CarState &cs) {
    if(cs.getSpeedX() < 0) return 1;
    if(abs(cs.getSpeedY()) > MAX_SKIDDING) return 0.1;
    
    return 0;
}

float OutOfTrack::getAccel(CarState &cs) {
    return(1-abs(cs.getSpeedY())*NEGATIVE_ACCEL_PERCENT); /* @todo can be negative, need some fix */
}

int OutOfTrack::getGear(CarState &cs) {
    if(cs.getSpeedX() > VELOCITY_GEAR_4) return cs.getGear(); //out of track the gear control based on velocity seems better than the one based on rpm
                                                            /* @todo need reverse behavior */
    if(cs.getSpeedX() > VELOCITY_GEAR_3) return 3;
    if(cs.getSpeedX() > VELOCITY_GEAR_2) return 2;
    
    return 1;
}

float OutOfTrack::getSteer(CarState &cs) {
	float angle = cs.getAngle();
    if(cs.getTrackPos() > 0){ //aim to go back to the track with a range of angles, between MIN_RETURN_ANGLE and MAX_RETURN_ANGLE with relation to the axis of track
        if(angle > MAX_RETURN_ANGLE) return 1;
        if(angle < MIN_RETURN_ANGLE) return -1;
    } else {
        if(angle < -(MAX_RETURN_ANGLE)) return -1;
        if(angle > -(MIN_RETURN_ANGLE)) return 1;
    }
    
    return 0;
}


OutOfTrack::~OutOfTrack() {}
