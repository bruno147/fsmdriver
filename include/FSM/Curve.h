#ifndef UNB_FSMDRIVER_STATE_CURVE_H
#define UNB_FSMDRIVER_STATE_CURVE_H

#include <cmath>
#include "DrivingState.h"
#include "StraightLine.h"

/**Class to treat curve state where the track has a minimal curvature. Note that this state is important at the race considering oponents with equal speed the way the driver complete the curve can achieve the lead at the race.*/
class Curve : public DrivingState {
public:
    Curve();
    // Curve(Curve const &);
    // void operator=(Curve const&);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    ~Curve();

private:
    int currentGear;

    float getAccel(CarState &cs);
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);/**Since the TORCS receive a value between -1 and 1 to the steer it used this function to normalize */
    float getSteer(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_CURVE_H
