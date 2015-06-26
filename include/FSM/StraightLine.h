/**  @file: StraightLine.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H
#define UNB_FSMDRIVER_STATE_STRAIGHT_LINE_H

#include "DrivingState.h"

/**Class to treat the state where there is a minimal curvature possible, this state is important considering that it can perform maximum speed.*/
 /*doc classe*/
class StraightLine : public DrivingState {
public:
    static int start_gear;
    // doc construtor
    StraightLine(int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                 int _arpm = 4000, int _hrpm = 9500);

    /* Inherited documentation. */
    CarControl drive(CarState &);

    // o pq de serem estaticos
    static int getGear(CarState &cs);

    void setParameters(int, int, int, int, int);

    ~StraightLine();

private:
    /** @todo documentar. Por que estáticos?
     * @todo deixar argumentos privados. */
    static int low_gear_limit;
    static int low_rpm;
    static int average_rpm;
    static int high_rpm;

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
