#include "OutOfTrack.h"

OutOfTrack::OutOfTrack(FSMDriver *o, float _ms, float _nap, int _vg4, int _vg3, int _vg2, float _maxra, float _minra)
                       : DrivingState(o) {
    MAX_SKIDDING = _ms;
    NEGATIVE_ACCEL_PERCENT = _nap;
    VELOCITY_GEAR_4 = _vg4;
    VELOCITY_GEAR_3 = _vg3;
    VELOCITY_GEAR_2 = _vg2;
    MAX_RETURN_ANGLE = _maxra;
    MIN_RETURN_ANGLE = _minra;
}

// OutOfTrack::OutOfTrack(OutOfTrack const &) {}

CarControl OutOfTrack::drive(CarState &cs) {
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
    /**Aim to go back to the track with a range of angles, between MIN_RETURN_ANGLE and MAX_RETURN_ANGLE with relation to the axis of track*/
    if(cs.getTrackPos() > 0){
        if(angle > MAX_RETURN_ANGLE) return 1;
        if(angle < MIN_RETURN_ANGLE) return -1;
    } else {
        if(angle < -(MAX_RETURN_ANGLE)) return -1;
        if(angle > -(MIN_RETURN_ANGLE)) return 1;
    }

    return 0;
}


OutOfTrack::~OutOfTrack() {}
