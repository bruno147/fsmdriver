#ifndef APPROACHINGCURVE_H
#define APPROACHINGCURVE_H

#include <cmath>
#include "FSM.h"
#include "StraightLine.h"

// extern const int INCREASE_GEAR_RPM;
extern float MAX_STEERING, TARGET_POS, BASE_SPEED;

class FSMDriver5;
/**Class to treat State where the section of the track before a curve, to better complete a curve it require a speed depending of the curve(for example how obligue it is) */
class ApproachingCurve : public DrivingState<FSMDriver5> {
public:
    static ApproachingCurve* instance();
    void enter(FSMDriver5 *driver);
    void exit(FSMDriver5 *driver);
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);

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
