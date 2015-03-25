#ifndef APPROACHINGCURVE_H
#define APPROACHINGCURVE_H

#include <cmath>
#include "FSM.h"
#include "StraightLine.h"

// extern const int INCREASE_GEAR_RPM;
extern float MAX_STEERING, TARGET_POS, BASE_SPEED;

class FSMDriver;

class ApproachingCurve : public DrivingState<FSMDriver> {
public:
    static ApproachingCurve* instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);

    ~ApproachingCurve();

private:
    bool sensorsAreUpdated;
    float rSensor, cSensor, lSensor, targetSpeed;

    ApproachingCurve();

    void updateSensors(CarState &cs);
    float getSteering(CarState &cs);
    float getBrake(CarState &cs);

    inline int getGear(CarState &cs) {
        return StraightLine::getGear(cs);
    }
    inline float getAccel(CarState cs) {
        return (cs.getSpeedX() > targetSpeed ? 0 : 1);
    }
    inline bool approachingRightTurn() {
        return (rSensor > lSensor);
    }
};



#endif // APPROACHINGCURVE_H
