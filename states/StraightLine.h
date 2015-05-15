#ifndef FSMDriver_STATE_STRAIGHTLINE_H
#define FSMDriver_STATE_STRAIGHTLINE_H

#include "FSM.h"
#include "Constants.h"

class FSMDriver;
/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
class StraightLine : public DrivingState<FSMDriver> {
public:
    static StraightLine *instance();
    void enter(FSMDriver *driver);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *FSMDriver, CarState &cs);
    static int getGear(CarState &cs);

    ~StraightLine();

private:
    StraightLine();
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);

    float getBrake(CarState &cs);

    static bool shouldDecreaseGear(int currentGear, int rpm);
    static inline bool runningOnLow(int rpm);
    static inline bool runningUnderAverage(int rpm);
    static inline bool runningOnHigh(int rpm);
    static inline bool isLowGear(int gear);
    static inline bool isHighGear(int gear);
    static inline bool shouldIncreaseGear(int currentGear, int rpm);
};

#endif // FSMDriver_STATE_STRAIGHTLINE_H
