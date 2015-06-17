#ifndef UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
#define UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H

#include <cmath>
#include "DrivingState.h"
#include "StraightLine.h"

/**Class to treat State where the section of the track before a curve, to better complete a curve it require a speed depending of the curve(for example how obligue it is) */
class ApproachingCurve : public DrivingState {
public:
    ApproachingCurve(int _ms = 0, int _tp = 0, int _bs = 0);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    ~ApproachingCurve();

public:
    /** @todo deixar argumentos privados. */
    float MAX_STEERING, TARGET_POS, BASE_SPEED;

    bool sensorsAreUpdated;
    float rSensor, cSensor, lSensor, targetSpeed;


    void updateSensors(CarState &cs);
    float getSteering(CarState &cs);
    float getBrake(CarState &cs);

    inline int getGear(CarState &cs);
    inline float getAccel(CarState cs);
    inline bool approachingRightTurn();
};



#endif // UNB_FSMDRIVER_STATE_APPROACHING_CURVE_H
