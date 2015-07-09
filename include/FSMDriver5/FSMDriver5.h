/**  @file: FSMDriver5.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_FSMDRIVER5_H
#define UNB_FSMDRIVER_FSMDRIVER5_H

#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>
#include <bitset>


/** @class FSMDriver5
*   @brief The driver with 5 states.
*
*   This class defines the driver based on a FSM, a controller with a 5-state.
*
*   Please note that this documentation provide information about the espefic files of the FSM driver,
*   the Loiacono's files(at src and include folder) have not been documented by us, for that reason the
*   Doxygen does not generate these files documentation, more information can be found at the own comments
*   of the code.
*   
*   @param max_straight_line_var upper boundary for classifying a straight line.
*   @param min_straight_line_var lower boundary for classifying a straight line.
*   @param max_approaching_curve_var upper boundary for classifying an approaching curve.
*   @param min_approaching_curve_var lower boundary for classifying an approaching curve.
*   
*/
class FSMDriver5 : public FSMDriver {
private:
    StraightLine straight_line;
    ApproachingCurve approaching_curve;
    Curve curve;
    OutOfTrack out_of_track;
    Stuck stuck;

    int segment_id;

    int max_straight_line_var;
    int min_straight_line_var;
    int max_approaching_curve_var;
    int min_approaching_curve_var;


public:
    virtual void onShutdown();
    virtual void onRestart();

    /** Initialization of the desired angles for the range finders. The angles are arbitrarily settled from
        −90 to 90 degrees in a 10 degree step. */
    /**
     * @brief init angles of range finders.
     * @details Initialization of the desired angles for the range finders. The angles are arbitrarily settled from
     *          −90 to 90 degrees in a 10 degree step.
     * 
     * @param angles values in degrees of the range finders.
     */
    virtual void init(float *angles);

    FSMDriver5();
    virtual ~FSMDriver5();

    /** Transitions between states (if appropriate). */
    void transition(CarState &);
};

#endif // UNB_FSMDRIVER_FSMDRIVER5_H
