#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "FSM.h"

constexpr float OVER_100_GEAR = 2; 
constexpr int START_GEAR = 1;
constexpr float STABLE_STEERING = 0.2;
constexpr float START_GEAR_MAX_SPEED = 75;
constexpr float SECOND_GEAR_MAX_SPEED = 100;

int gear = START_GEAR;

float defined_steer[25]={0,0.02,0.05,0.1,0.12,0.15,0.18,0.20,0.2,0.22,0.25,0.28,0.3,0.32,0.35,0.38,0.40,0.42,0.45,0.48,0.50,0.52};// defined steer to each angle and track limiters
float angle_limiter[10]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
float track_limiter[15]={0.05,0.1,0.2,0.25,0.30,0.4,0.5,0.55,0.60,0.65,0.7,0.8,0.9,1};

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
	
    int getGear(float steer, int gear, float speedX) {
		
		if(steer > STABLE_STEERING && gear > START_GEAR){
			--gear;
		}
		else {
			if(speedX < START_GEAR_MAX_SPEED) {
				gear = START_GEAR;
			}
			else{
				if(speedX < SECOND_GEAR_MAX_SPEED) {
					gear = START_GEAR + 1;
				}
			}
		}

	return gear;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
		float angle = cs.getAngle();
		bool is_positive_angle = (angle > 0);
		
		angle = abs(angle);
		int a = 0; 
		while(angle < angle_limiter[a]) ++a;
		/* a value will *not* exceed array size because getAngle() range is 
		within angle_limiter bounds. */

		float track_axis_distance = abs(cs.getTrackPos());
		int t = 0;
		while(track_axis_distance < track_limiter[t]) ++t;
		/* t value will *not* exceed array size because getTrackPos() range is 
		within track_limiter bounds. */

		float steer = (is_positive_angle ? -defined_steer[a+t] : defined_steer[a+t]);

		gear = getGear(steer, gear, cs.getSpeedX());

		float accel  = (gear > OVER_100_GEAR ? 0 : 1);
		constexpr int brake = 0;
		float clutch = (gear > OVER_100_GEAR ? 1 : 0);

		return CarControl(accel, brake, gear, steer, clutch);
	}

    ~Curve(){}
};

#endif // FSMDRIVER_STATE_CURVE_H
