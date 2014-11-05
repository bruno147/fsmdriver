#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include "FSM.h"

class FSMDriver;

const float MAX_SKIDDING = 3;
const float NEGATIVE_ACCEL_PERCENT = 0.1;
const int VELOCITY_GEAR_4 = 90;
const int VELOCITY_GEAR_3 = 70;
const int VELOCITY_GEAR_2 = 40;
const float MAX_RETURN_ANGLE = 0.7;
const float MIN_RETURN_ANGLE = 0.5;

class OutOfTrack : public DrivingState<FSMDriver> {
public:
    static OutOfTrack *instance() {
        static OutOfTrack instance;
        return &instance;
    }

private:
    OutOfTrack() {}
    OutOfTrack(OutOfTrack const &);
    void operator=(OutOfTrack const&);

public:
    ~OutOfTrack(){}

    void enter(FSMDriver *driver) {
        cout << "Enter OutOfTrack" << endl;
    }

    void exit(FSMDriver *driver) {
        cout << "Exit OutOfTrack" << endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
        const float clutch = 0;
        const int focus = 0, meta = 0;

	    return CarControl(getAccel(cs), getBrake(cs), getGear(cs), getSteer(cs), clutch, focus, meta);
	}

private:
    float getBrake(CarState &cs) {
        if(cs.getSpeedX() < 0) return 1;
        if(abs(cs.getSpeedY()) > MAX_SKIDDING) return 0.1;
        
        return 0;
	}

    float getAccel(CarState &cs) {
        return(1-abs(cs.getSpeedY())*NEGATIVE_ACCEL_PERCENT); /* @todo can be negative, need some fix */
    }

    int getGear(CarState &cs) {
        if(cs.getSpeedX() > VELOCITY_GEAR_4) return cs.getGear(); //out of track the gear control based on velocity seems better than the one based on rpm
                                                                /* @todo need reverse behavior */
        if(cs.getSpeedX() > VELOCITY_GEAR_3) return 3;
        if(cs.getSpeedX() > VELOCITY_GEAR_2) return 2;
        
        return 1;
	}

	float getSteer(CarState &cs) {
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

};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
