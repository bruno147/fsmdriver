/**  @file: FSMDriver.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#ifndef UNB_FSMDRIVER_FSM_H
#define UNB_FSMDRIVER_FSM_H

#include "DrivingState.h"
#include "WrapperBaseDriver.h"

/** A Finite State Machine controller for TORCS. */
class FSMDriver : public WrapperBaseDriver {
public:
	/** Constructor. */
	FSMDriver();

	/** Virtual destructor. */
	virtual ~FSMDriver();

	/** Changes the FSM's current state.
	 *
	 * @param state a pointer to the state to change to. */
	void change_to(DrivingState *state);

	/** Changes the FSM's current state to its previous state. */
	void revert_state();

	/** Analyses the given perception and transitions between states accordingly.
     *
	 * @param cs the driver's perception of the environment. */
    virtual void transition(CarState &cs) = 0;

	/** Defines the controllers actions based on its perception.
	 *
	 * @param cs the driver's perception of the environment.
	 * @return the actions to take. */
    CarControl wDrive(CarState cs);

protected:
	/** Pointer to the FSM's current state. */
	DrivingState *current_state;

private:
	/** Pointer to the state the FSM was previously in. */
	DrivingState *previous_state;
};

#endif // UNB_FSMDRIVER_FSM_H
