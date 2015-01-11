#ifndef FSMDRIVER_STATE_STRAIGHTLINE_H
#define FSMDRIVER_STATE_STRAIGHTLINE_H

#include "FSM.h"

static const int START_GEAR = 1;

class FSMDriver;
class StraightLine : public DrivingState<FSMDriver> {
public:
    
    static float LOW_GEAR_LIMIT;
    static float LOW_RPM;
    static float AVERAGE_RPM;
    static float HIGH_RPM;

    static StraightLine *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    static int getGear(CarState &cs);

    ~StraightLine();

private:
    StraightLine();
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);

    float getBrake(CarState &cs);

    static bool shouldDecreaseGear(int currentGear, int rpm);
    static inline bool runningOnLow(int rpm) {
        return (rpm < LOW_RPM);
    }
    static inline bool runningUnderAverage(int rpm) {
        return (rpm <= AVERAGE_RPM);
    }
    static inline bool runningOnHigh(int rpm) {
        return (rpm > HIGH_RPM);
    }
    static inline bool isLowGear(int gear) {
        return (gear > START_GEAR && gear < LOW_GEAR_LIMIT);
    }
    static inline bool isHighGear(int gear) {
        return (gear >= LOW_GEAR_LIMIT);
    }
    static inline bool shouldIncreaseGear(int currentGear, int rpm) {
        return runningOnHigh(rpm);
    }
};


#endif // FSMDRIVER_STATE_STRAIGHTLINE_H
