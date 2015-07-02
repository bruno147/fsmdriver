/**  @file: FSMDriver3.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_FSMDRIVER3_H
#define UNB_FSMDRIVER_FSMDRIVER3_H

#include <vector>
#include <fstream>
#include <algorithm>

#include "InsideTrack.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "FSMDriver.h"
#include "Knowledge.h"

/** @class FSMDriver3
*   @brief The driver itself.
*
*   This class defines the driver based on a FSM.
*
*   Please note that this documentation provide information about the espefic files of the newFSM driver,
*   the Loiacono's files(at src and include folder) have not been documented by us, for that reason the
*   Doxygen does not generate these files documentation, more information can be found at the own comments
*   of the code.
*/

class FSMDriver3 : public FSMDriver {
private:
    // States.
    InsideTrack inside_track;
    OutOfTrack out_of_track;
    Stuck stuck;

public:
    /** Called when the driver finishes the race. */
    virtual void onShutdown();
    /** Called when TORCS asks a race restart. */
    virtual void onRestart();

    /**Initialization of the desired angles for the rangefinders. It Initialize the NUM_SENSORS track's angles using a gausian 
    *configuration in order directed more sensors in the front of the car and consequently improve a curve detection 
    */
    virtual void init(float *angles);
    /** Empty constructor. */
    FSMDriver3();
    /** Empty destructor */
    virtual ~FSMDriver3();
    //! Transitions between states.
    /*!
    *   This method decides whenever the current state does not fit with the car status and needs to be changed.The transition choose the most fitted state at the moment of the race.
    *   The transition check if the car is stuck by the it's speed, if it is lower than certain value for long enough it is stuck, if it is not, the function check the car is inside or
    *   out side the track using tracks sensors than choosing the appropriate state.
    *	@param cs a data structure cointaining information from the car's sensors.
    */
    void transition(CarState &cs);
    /**
     * @brief Set Road Parameters.
     * @details Set all states with the parameters found with Genetic Algorithm, for road tracks.
     */
    void setROAD();
    /**
     * @brief Set Dirt Parameters.
     * @details Set all states with the parameters found with Genetic Algorithm, for dirt tracks.
     */
    void setDIRT();
};

#endif // FSMDriver3_H
