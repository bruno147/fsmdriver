#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "FSM.h"


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
		int gear = StraightLine::getGear(cs);
		float accel  = getAccel(cs);
        float brake = getBrake(cs);
		float clutch = 0;

		return CarControl(accel, brake, gear, steer, clutch);
	}

    ~Curve(){}

private:
    float getAccel(CarState &cs) { //@todo Change accelaration logic.
    	return 0.6;
    }
    bool isFacingWrongWay(CarState &cs) {
        return cs.getAngle() < -M_PI/2 || cs.getAngle() > M_PI/2;
    }
    float getBrake(CarState cs) {
    	return (cs.getSpeedX() < 0 ? 1:0);
    }

    float findFarthestDirection(CarState &cs) {
        float farthestSensor = -INFINITY;
        float farthestDirection = 0;
        for (int i = 0; i < 19; i++) {
            if (farthestSensor < cs.getTrack(i)) {
                farthestSensor = cs.getTrack(i);
                farthestDirection = i;
            }
        }
        farthestDirection = -M_PI/2 + farthestDirection*M_PI/18;
        return normalizeSteer(-farthestDirection);
    }

    float normalizeSteer(float angle) {
        const float MAXSTEER = 0.785398;
        return angle/MAXSTEER;
    }

    float getSteer(CarState &cs) {
        return isFacingWrongWay(cs) ? cs.getAngle() : findFarthestDirection(cs);
    }

};

#endif // FSMDRIVER_STATE_CURVE_H
