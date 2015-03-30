#ifndef FSMDRIVER_STATE_TRACK_H
#define FSMDRIVER_STATE_TRACK_H

#include <cmath>
#include "FSM.h"

//-----------------------------------------------------------------

extern int START_GEAR;
extern int LOW_GEAR_LIMIT;
extern int LOW_RPM;
extern int AVERAGE_RPM;
extern int HIGH_RPM;
extern int currentGear;
//-----------------------------------------------------------------

class FSMDriver;

class InsideTrack : public DrivingState<FSMDriver> {
public:
    static InsideTrack *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    int getGear(CarState &cs);
    ~InsideTrack();

private:
    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);
    int currentGear;
    float distance;

    bool shouldDecreaseGear(int currentGear, int rpm);
    inline bool runningOnLow(int rpm);
    inline bool runningUnderAverage(int rpm);
    inline bool runningOnHigh(int rpm);
    inline bool isLowGear(int gear);
    inline bool isHighGear(int gear);
    inline bool shouldIncreaseGear(int currentGear, int rpm);
    float getAccel(CarState &cs);
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs,float &distance);
    float normalizeSteer(float angle);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
