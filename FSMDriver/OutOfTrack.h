#ifndef FSMDRIVER_STATE_OUTOFTRACK_H
#define FSMDRIVER_STATE_OUTOFTRACK_H

#include "State.h"

class OutOfTrack : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver) {
	    CarState& cs = fsmdriver->getCarState();
	    CarControl cc(this->getAccel(cs), this->getBrake(cs), this->getGear(cs), this->getSteer(cs), 0, 0, 0);
	    return cc;
	}
    static OutOfTrack* Instance() {
        static OutOfTrack instance;
        return &instance;
    }

    ~OutOfTrack(){}
private:
    OutOfTrack(){}
    float getBrake(CarState & cs){
    if(abs(cs.getSpeedY())>3){              //if the vehicle begins to skidding bigger than 3m/s in axis Y the brake will return 0.1
        return 0.1;
    }else{
        return 0;
    	}
	}

    float getAccel(CarState & cs){
    return(1-abs(cs.getSpeedY())*0.1);        //can be negative, need some fix
	}

    int getGear(CarState & cs){
    if(cs.getSpeedX()>90){                      //out of track the gear control based on velocity seems better than the one based on rpm
        return cs.getGear();                    //need reverse behavior 
    }else if(cs.getSpeedX()>70){
        return 3;
    }else if(cs.getSpeedX()>40){
        return 2;
    }else{
        return 1;
    	}
	}

	float getSteer(CarState & cs){
	    if(cs.getTrackPos()>0){                 //aim to go back to the track with a range of angles, between 40 and 28 with relation to the axis of track
	        if(cs.getAngle()>0.7){              //0.7rad is about 40 degrees
	            return 1;
	        }else if(cs.getAngle()<0.5){        //0.5rad is about 28 degress, this values are just a guess
	            return -1;
	        }
	    }else{
	        if(cs.getAngle()<-0.7){
	            return -1;
	        }else if(cs.getAngle()<0.5){
	            return 1;
	        }
	    }
	}

};

#endif // FSMDRIVER_STATE_OUTOFTRACK_H
