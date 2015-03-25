#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include <cmath>
#include "FSM.h"
#include "StraightLine.h"


class FSMDriver;

class Curve : public DrivingState<FSMDriver> {
public:
    static Curve *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);

    ~Curve();

private:
    int currentGear;

    Curve();
    Curve(Curve const &);
    void operator=(Curve const&);

    float getAccel(CarState &cs);
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_CURVE_H
