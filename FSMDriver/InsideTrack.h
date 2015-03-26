#ifndef FSMDRIVER_STATE_TRACK_H
#define FSMDRIVER_STATE_TRACK_H

#include <cmath>
#include "FSM.h"

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
    int START_GEAR;
    int LOW_GEAR_LIMIT;
    int LOW_RPM;
    int AVERAGE_RPM;
    int HIGH_RPM;
    int currentGear;

    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);

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
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
