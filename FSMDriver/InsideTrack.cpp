#include "InsideTrack.h"


int START_GEAR = 1;
/*int LOW_GEAR_LIMIT = 4;

int LOW_RPM = 1500;
int AVERAGE_RPM = 4000;
int HIGH_RPM = 9500;*/

InsideTrack::InsideTrack() : currentGear(START_GEAR) {}

InsideTrack::InsideTrack(InsideTrack const &) {}

InsideTrack *InsideTrack::instance() {
    static InsideTrack instance;
    return &instance;
}

void InsideTrack::enter(FSMDriver *driver) {
    cout << "Enter InsideTrack" << endl;
}

void InsideTrack::exit(FSMDriver *driver) {
    cout << "Exit InsideTrack" << endl;
}

CarControl InsideTrack::drive(FSMDriver *fsmdriver, CarState &cs) {
	float steer = getSteer(cs);
	int gear = getGear(cs);
	float accel  = getAccel(cs);
    float brake = getBrake(cs);
	float clutch = 0;

	return CarControl(accel, brake, gear, steer, clutch);
}
int InsideTrack::getGear(CarState &cs) {
    int gear = cs.getGear();
    if(gear <= 0) return START_GEAR;

    int rpm = cs.getRpm();

    if(shouldIncreaseGear(gear, rpm)) ++gear;
    else if(shouldDecreaseGear(gear, rpm)) --gear;

    return gear;
}

bool InsideTrack::shouldDecreaseGear(int currentGear, int rpm) {
    if(isLowGear(currentGear) && runningOnLow(rpm)) return true;
    if(isHighGear(currentGear) && runningUnderAverage(rpm)) return true;
    return false;
}

inline bool InsideTrack::runningOnLow(int rpm) {
    return (rpm < LOW_RPM);
}

inline bool InsideTrack::runningUnderAverage(int rpm) {
    return (rpm <= AVERAGE_RPM);
}

inline bool InsideTrack::runningOnHigh(int rpm) {
    return (rpm > HIGH_RPM);
}

inline bool InsideTrack::isLowGear(int gear) {
    return (gear > START_GEAR && gear < LOW_GEAR_LIMIT);
}

inline bool InsideTrack::isHighGear(int gear) {
    return (gear >= LOW_GEAR_LIMIT);
}

inline bool InsideTrack::shouldIncreaseGear(int currentGear, int rpm) {
    return runningOnHigh(rpm);
}



float InsideTrack::getAccel(CarState &cs) { //@todo Change accelaration logic.
	return 0.6;
}

bool InsideTrack::isFacingWrongWay(CarState &cs) {
    return cs.getAngle() < -M_PI/2 || cs.getAngle() > M_PI/2;
}

float InsideTrack::getBrake(CarState cs) {
	return (cs.getSpeedX() < -2 ? 1:0);
}

float InsideTrack::findFarthestDirection(CarState &cs) {
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

float InsideTrack::normalizeSteer(float angle) {
    const float MAXSTEER = 0.785398;
    return angle/MAXSTEER;
}

float InsideTrack::getSteer(CarState &cs) {
    return isFacingWrongWay(cs) ? cs.getAngle() : findFarthestDirection(cs);
}

InsideTrack::~InsideTrack() {}
