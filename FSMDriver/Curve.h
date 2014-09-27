#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "State.h"

class Curve : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver) {
	    CarState cs = fsmdriver->getCarState();
	    int gear = 1;
	    float steer = 0;
	    int gear0[3]={-1,1,2};//This set of gear were defined by tests
	    float steer0[5]={0.1,0.6,-0.4,-0.8,-1};//This set of steer were defined by tests
	    float accel,accel0[3]={0,0.5,1};//This set of accel were defined by tests
	    float angle,angle_lim[4]={3.1415/2-1,-3.1415/2+1,0.1,-0.1};// angle and angles limits in this code
	    float track_dis,track_lim[2]={0.2,-0.2};
	    float factor[2]={1.5,1.2};//proportionate fator to steer, track_dis and angle


	    accel=accel0[2];
	    steer=steer0[0];
	    gear = gear0[1];

	    track_dis=cs.getTrackPos();
	    angle = cs.getAngle();

	    //printf("%f %f\n",angle,track_dis);
	        if(((angle<angle_lim[0])&&(angle>angle_lim[1]))){// In the case the car is in the right direction

	            if(((angle<angle_lim[2])&&(angle>angle_lim[3]))){

	                if(((track_dis>track_lim[0])||(track_dis<track_lim[1]))){ //change the steer when the car is in a turn
	                    gear =gear0[1];
	                    steer=factor[0]*steer0[2]*track_dis;
	                    accel = accel0[2];

	                }

	                else{
	                    if((steer>0.05)&&(steer<-0.05)){
	                        steer = steer-0.0001*steer/abs(steer);// Try to minimaze the steer when the condition of the track normalize(retiline) in order to maximaxe the speed
	                    }
	                    accel= accel0[2];
	                    if(gear<5){
	                        gear=gear+1;
	                    }

	                }
	            }

	            else{

	                steer=-factor[1]*steer0[2]*angle/abs(angle);// Adjust the steer according with the angle.
	                gear = gear0[1];
	                accel = accel0[1];


	            }

	        }

	        else{ //In the case the car is NOT in the right direction
	            accel = accel0[1];
	            steer= -steer0[3]*angle/abs(angle);
	            gear = gear0[1];
	        }

	    CarControl cc(accel,0,gear,steer,0);

	    return cc;

	}

    Curve(){}
    ~Curve(){}
};

#endif // FSMDRIVER_STATE_CURVE_H