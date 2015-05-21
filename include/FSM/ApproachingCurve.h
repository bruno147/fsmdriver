#ifndef APPROACHINGCURVE_H
#define APPROACHINGCURVE_H

#include "StraightLine.h"

// extern const int INCREASE_GEAR_RPM;
extern float MAX_STEERING, TARGET_POS;//, BASE_SPEED;

/**Class to treat State where the section of the track before a curve, to better complete a curve it require a speed depending of the curve(for example how obligue it is) */
class ApproachingCurve : public DrivingState {
public:
    static ApproachingCurve* instance();
    void enter(BaseDriver *driver);
    void exit(BaseDriver *driver);
    virtual CarControl drive(BaseDriver *driver, CarState &cs);

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
