/**  @file: DrivingState.h
 * @author: Bruno Macedo, Gabriel Araujo, Gabriel Sousa, Matheus Crestani, Yuri Galli, Guilherme N. Ramos (gnramos@unb.br)
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_DRIVING_STATE_H
#define UNB_FSMDRIVER_DRIVING_STATE_H

#include "CarControl.h"
#include "CarState.h"

class FSMDriver;

/** Abstract class defining a state for a Finite State Machine controller. */
class DrivingState {
public:
	/** Construtor.
	 *
	 * @param o a pointer to the driver that owns the state. */
	DrivingState();

	/** Virtual destructor. */
    virtual ~DrivingState();

    /** Defines the driving policy of the state.
     *
     * @param cs the driver's perception of the environment. */
    virtual CarControl drive(CarState &cs) = 0;

    /** Called when entering the state. */
    virtual void enter();

    /** Called when exiting the state. */
    virtual void exit();
};

#endif // UNB_FSMDRIVER_DRIVING_STATE_H
