#ifndef UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
#define UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H

#include <cmath>
#include "FSM.h"
#include "StraightLine.h"

class FSMDriver5;
/**Class to treat State where the section of the track before a curve, to better complete a curve it require a speed depending of the curve(for example how obligue it is) */
class ApproachingCurve : public DrivingState<FSMDriver5> {
public:
    ApproachingCurve(int _ms = 0, int _tp = 0, int _bs = 0);
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);

    ~ApproachingCurve();

private:
    float MAX_STEERING, TARGET_POS, BASE_SPEED;

    bool sensorsAreUpdated;
    float rSensor, cSensor, lSensor, targetSpeed;


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



#endif // UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
