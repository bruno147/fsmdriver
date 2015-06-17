#ifndef UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H
#define UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H

#include "DrivingState.h"

/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
class StraightLine : public DrivingState {
public:
    static int start_gear;

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
    static int low_gear_limit;
    static int low_rpm;
    static int average_rpm;
    static int high_rpm;
private:

    float getBrake(CarState &cs);

    static bool shouldDecreaseGear(int current_gear, int rpm);
    static inline bool runningOnLow(int rpm);
    static inline bool runningUnderAverage(int rpm);
    static inline bool runningOnHigh(int rpm);
    static inline bool isLowGear(int gear);
    static inline bool isHighGear(int gear);
    static inline bool shouldIncreaseGear(int current_gear, int rpm);
};

#endif // UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H
