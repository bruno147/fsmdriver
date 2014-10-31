#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "FSM.h"


int gear = 1;
float SpeedX;
float accel=1;
float steer = 0,defined_steer[25]={0,0.02,0.05,0.1,0.12,0.15,0.18,0.20,0.2,0.22,0.25,0.28,0.3,0.32,0.35,0.38,0.40,0.42,0.45,0.48,0.50,0.52};// defined steer to each angle and track limiters
float clutch=0;
float brake=0;
float angle,angle_limiter[10]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
float track_axis_distance,track_limiter[15]={0.05,0.1,0.2,0.25,0.30,0.4,0.5,0.55,0.60,0.65,0.7,0.8,0.9,1};
float direction_angle;
int size_angle_limiter,size_track_limiter; 
int contator_angle_limiter,contator_track_limiter;// contator_angle and contator_track 

class FSMDriver;

class Curve : public DrivingState<FSMDriver> {
public:
    static Curve *instance() {
        static Curve instance;
        return &instance;
    }

private:
    Curve() {}
    Curve(Curve const &);
    void operator=(Curve const&);

public:

    void enter(FSMDriver *driver) {
        std::cout << "Enter Curve" << std::endl;
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit Curve" << std::endl;
    }
	
    int getgear(float steer, int gear,float SpeedX){
		
		if((steer>0.2)&&(gear>1)){
			gear=gear -1;
		}
		else{
			if(SpeedX < 75){
				gear = 1;
			}
			else{
				if(SpeedX < 100){
					gear = 2;
				}
			}
		}

    return gear;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {

		clutch=0;
		brake=0;		
		size_angle_limiter=sizeof(angle_limiter);
		size_track_limiter=sizeof(track_limiter);
		SpeedX = cs.getSpeedX();
		angle = cs.getAngle();
		track_axis_distance = cs.getTrackPos();
		direction_angle = (angle>0?-1:+1);

		for(contator_angle_limiter=0;(contator_angle_limiter<size_angle_limiter);contator_angle_limiter++){//this loop allow to find the angle interval at the race

			if(angle<abs(angle_limiter[size_angle_limiter])){
		
				for(contator_track_limiter=0;(contator_track_limiter<size_track_limiter);contator_track_limiter++){//this loop allow to find the track distance interval at the race

					if(track_axis_distance<abs(track_limiter[contator_track_limiter])){
						steer = direction_angle*defined_steer[contator_track_limiter+contator_angle_limiter];		
						contator_angle_limiter = size_angle_limiter;
						contator_track_limiter = size_track_limiter;
					}
				}	
			}
		}

		gear=getgear(steer,gear,SpeedX);

		if(gear>2){// to assure a better performance the curve must be done reducing velocity using clutch and accel = 0
			accel=0;
			clutch = 1;				
		}

		CarControl cc(accel,brake,gear,steer,clutch);

return cc;

	}

    ~Curve(){}
};

#endif // FSMDRIVER_STATE_CURVE_H
