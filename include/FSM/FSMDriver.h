/**  @file: FSMDriver.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_FSM_H
#define UNB_FSMDRIVER_FSM_H

#define UNKN   0
#define ROAD   1
#define DIRT   2

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
	void changeTo(DrivingState *state);

	/** Changes the FSM's current state to its previous state. */
	void revertState();

	/** Analyses the given perception and transitions between states accordingly.
     *
	 * @param cs the driver's perception of the environment. */
    virtual void transition(CarState &cs) = 0;

	/** Defines the controllers actions based on its perception.
	 *
	 * @param cs the driver's perception of the environment.
	 * @return the actions to take. */
    CarControl wDrive(CarState cs);

	/** Pointer to the FSM's current state. */
	DrivingState *current_state;
	/** Pointer to the state the FSM was previously in. */
	DrivingState *previous_state;

	/** Indicates wich state of the test track was, unknown or road or dirt. */
	int tested;
	/** Indicates wich track the drive is, road or dirt. */
	std::string road_or_dirt;
// protected:
private:
	/** Distance covered in braking. */
	float dist;
	/** Threshold value for decide if the track is road or dirt. */
	float threshold;
	CarControl testTrack(CarState cs);
};

#endif // UNB_FSMDRIVER_FSM_H
