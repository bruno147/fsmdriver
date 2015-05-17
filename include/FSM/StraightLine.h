#ifndef UNB_FSMDRIVER_STATE_STRAIGHTLINE_H
#define UNB_FSMDRIVER_STATE_STRAIGHTLINE_H

#include "DrivingState.h"

/******************************************************************************/
extern int START_GEAR; // = 1;
extern int LOW_GEAR_LIMIT; // = 4;

extern int LOW_RPM; // = 1500;
extern int AVERAGE_RPM; // = 4000;
extern int HIGH_RPM; // = 9500;
/******************************************************************************/

/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
class StraightLine : public DrivingState {
public:
    static StraightLine *instance();
    virtual CarControl drive(BaseDriver *driver, CarState &cs);
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

#endif // UNB_FSMDRIVER_STATE_STRAIGHTLINE_H
