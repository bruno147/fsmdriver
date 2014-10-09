#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include "FSM.h"

class FSMDriver;

class OutOfTrack : public DrivingState<FSMDriver> {
public:
    static OutOfTrack *instance() {
        static OutOfTrack instance;
        return &instance;
    }

private:
    OutOfTrack() : 
        MAX_SKIDDING(3), NEGATIVE_ACCEL_PERCENT(0.1), 
        VELOCITY_GEAR_4(90), VELOCITY_GEAR_3(70), 
        VELOCITY_GEAR_2(40), MAX_RETURN_ANGLE(0.7),
        MIN_RETURN_ANGLE(0.5) {}
    OutOfTrack(OutOfTrack const &);
    void operator=(OutOfTrack const&);

public:
    void enter(FSMDriver *driver) {
        std::cout << "Enter OutOfTrack" << std::endl;
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit OutOfTrack" << std::endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
	    CarControl cc(this->getAccel(cs), this->getBrake(cs), this->getGear(cs), this->getSteer(cs), 0, 0, 0);
	    return cc;
	}
    static OutOfTrack* Instance() {
        static OutOfTrack instance;
        return &instance;
    }

    ~OutOfTrack(){}

private:
    float MAX_SKIDDING;
    float NEGATIVE_ACCEL_PERCENT;
    int VELOCITY_GEAR_4;
    int VELOCITY_GEAR_3;
    int VELOCITY_GEAR_2;
    float MAX_RETURN_ANGLE;
    float MIN_RETURN_ANGLE;

    float getBrake(CarState & cs){
        if(cs.getSpeedX()<0) return 1;
        if(abs(cs.getSpeedY()) > MAX_SKIDDING) return 0.1;
        
        return 0;
	}

    float getAccel(CarState & cs){
        return(1-abs(cs.getSpeedY())*NEGATIVE_ACCEL_PERCENT);        //can be negative, need some fix
    }

    int getGear(CarState & cs){
        if(cs.getSpeedX()>VELOCITY_GEAR_4) return cs.getGear(); //out of track the gear control based on velocity seems better than the one based on rpm
                                                                //need reverse behavior 
        if(cs.getSpeedX()>VELOCITY_GEAR_3) return 3;
        if(cs.getSpeedX()>VELOCITY_GEAR_2) return 2;
        
        return 1;
	}

	float getSteer(CarState & cs){
	    if(cs.getTrackPos()>0){                             //aim to go back to the track with a range of angles, between 40 and 28 with relation to the axis of track
	        if(cs.getAngle()>MAX_RETURN_ANGLE) return 1;    //0.7rad is about 40 degrees
	        if(cs.getAngle()<MIN_RETURN_ANGLE) return -1;  //0.5rad is about 28 degress, this values are just a guess
	    } else {
	        if(cs.getAngle()<-(MAX_RETURN_ANGLE)) return -1;
	        if(cs.getAngle()>-(MIN_RETURN_ANGLE)) return 1;
	    }
        
        return 0;
	}

};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
