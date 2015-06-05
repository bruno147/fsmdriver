#ifndef UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H
#define UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H

#include "FSM.h"

/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
class StraightLine : public DrivingState {
public:
    static int START_GEAR;

    StraightLine(FSMDriver *o, int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                 int _arpm = 4000, int _hrpm = 9500);
    // StraightLine(StraightLine const &);
    // void operator=(StraightLine const&);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    static int getGear(CarState &cs);

    ~StraightLine();

public:
    /** @todo documentar. Por que estáticos?
     * @todo deixar argumentos privados. */
    static int LOW_GEAR_LIMIT;
    static int LOW_RPM;
    static int AVERAGE_RPM;
    static int HIGH_RPM;
private:

    float getBrake(CarState &cs);

    static bool shouldDecreaseGear(int currentGear, int rpm);
    static inline bool runningOnLow(int rpm);
    static inline bool runningUnderAverage(int rpm);
    static inline bool runningOnHigh(int rpm);
    static inline bool isLowGear(int gear);
    static inline bool isHighGear(int gear);
    static inline bool shouldIncreaseGear(int currentGear, int rpm);
};

#endif // UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H
