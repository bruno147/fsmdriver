#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "FSM.h"

/******************************************************************************/
extern const int START_GEAR;

const float OVER_100_GEAR = 2;  /* @todo isso depende do carro, não deveria ser assim. */
const float STABLE_STEERING = 0.2;
const float START_GEAR_MAX_SPEED = 75; /* @todo isso depende do carro, não deveria ser assim. */
const float SECOND_GEAR_MAX_SPEED = 100; /* @todo isso depende do carro, não deveria ser assim. */

float defined_steer[25]={0,0.02,0.05,0.1,0.12,0.15,0.18,0.20,0.2,0.22,0.25,0.28,0.3,0.32,0.35,0.38,0.40,0.42,0.45,0.48,0.50,0.52};// defined steer to each angle and track limiters
float angle_limiter[10]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
float track_limiter[15]={0.05,0.1,0.2,0.25,0.30,0.4,0.5,0.55,0.60,0.65,0.7,0.8,0.9,1};
/******************************************************************************/

class FSMDriver;

class Curve : public DrivingState<FSMDriver> {
public:
    static Curve *instance() {
        static Curve instance;
        return &instance;
    }

private:
    Curve() : currentGear(START_GEAR) {}
    Curve(Curve const &);
    void operator=(Curve const&);
    int currentGear;

public:
    void enter(FSMDriver *driver) {
        cout << "Enter Curve" << endl;
    }

    void exit(FSMDriver *driver) {
        cout << "Exit Curve" << endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
		float steer = getSteer(cs);
		currentGear = getGear(steer, cs.getSpeedX());

		float accel  = (currentGear > OVER_100_GEAR ? 0 : 1);
		const int brake = 0;
		float clutch = (currentGear > OVER_100_GEAR ? 1 : 0);

		return CarControl(accel, brake, currentGear, steer, clutch);
	}

    ~Curve(){}

private:
	inline bool shouldDecreaseGear(float steer) {
		return (steer > STABLE_STEERING && currentGear > START_GEAR);
	}
    inline bool shouldIncreaseGear(int currentGear, int rpm) {
	}

    int getGear(float steer, float speedX) {
		if(shouldDecreaseGear(steer))
			return currentGear-1;

		if(speedX < START_GEAR_MAX_SPEED)
			return START_GEAR;

		if(speedX < SECOND_GEAR_MAX_SPEED)
			return = START_GEAR + 1;

		return currentGear;
    }

    float getSteer(CarState &cs) {
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

		return (is_positive_angle ? -defined_steer[a+t] : defined_steer[a+t]);
	}
};

#endif // FSMDRIVER_STATE_CURVE_H
