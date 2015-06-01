#ifndef FSMDriver5_STATE_STRAIGHTLINE_H
#define FSMDriver5_STATE_STRAIGHTLINE_H

#include "FSM.h"

class FSMDriver5;
/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
class StraightLine : public DrivingState<FSMDriver5> {
public:
    static int START_GEAR;
    
    StraightLine(int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                 int _arpm = 4000, int _hrpm = 9500);
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);
    
    virtual CarControl drive(FSMDriver5 *FSMDriver5, CarState &cs);
    static int getGear(CarState &cs);

    ~StraightLine();

private:
    static int LOW_GEAR_LIMIT;
    static int LOW_RPM;
    static int AVERAGE_RPM;
    static int HIGH_RPM;


    float getBrake(CarState &cs);

    static bool shouldDecreaseGear(int currentGear, int rpm);
    static inline bool runningOnLow(int rpm);
    static inline bool runningUnderAverage(int rpm);
    static inline bool runningOnHigh(int rpm);
    static inline bool isLowGear(int gear);
    static inline bool isHighGear(int gear);
    static inline bool shouldIncreaseGear(int currentGear, int rpm);
};

#endif // FSMDriver5_STATE_STRAIGHTLINE_H
