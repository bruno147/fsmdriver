#ifndef UNB_FSMDRIVER_FSM_H
#define UNB_FSMDRIVER_FSM_H

#include "WrapperBaseDriver.h"

class FSMDriver;

/** Abstract class defining a state for a Finite State Machine controller. */
class DrivingState {
public:
	/** Construtor.
	 *
	 * @param o a pointer to the driver that owns the state. */
	DrivingState(FSMDriver *o) : owner(o) {
		assert(owner);
	}

	/** Virtual destructor. */
    virtual ~DrivingState() {}

    /** Defines the driving policy of the state.
     *
     * @param cs the driver's perception of the environment. */
    virtual CarControl drive(CarState &cs) = 0;

    /** Called when entering the state. */
    virtual void enter(){}

    /** Called when exiting the state. */
    virtual void exit(){}

protected:
	/** Pointer to the driver that owns the state. */
	FSMDriver *owner;
};

/** A Finite State Machine controller. */
class FSMDriver : public WrapperBaseDriver {
public:
	/** Constructor.
	 *
	 * @param initial_state a pointer to the state the FSM starts in. */
	FSMDriver() : previous_state(nullptr), current_state(nullptr) {
	}

	/** Virtual destructor. */
	virtual ~FSMDriver() {}

	/** Changes the FSM's current state.
	 *
	 * @param state a pointer to the state to change to. */
	void change_to(DrivingState *state) {
		assert(state);
		previous_state = current_state;
		current_state = state;
	}

	/** Changes the FSM's current state to its previous state. */
	void revert_state() {
		change_to(previous_state);
	}
	/** Analyses the given perception and, if necessary,  transitions to a
	 * different state.
     *
	 * @param cs the driver's perception of the environment. */
    virtual void transition(CarState &cs) = 0;

	/** Defines the controllers actions based on its perception.
	 *
	 * @param cs the driver's perception of the environment.
	 * @return the actions to take. */
    CarControl wDrive(CarState cs) {
		transition(cs);
		return current_state->drive(cs);
	}

private:
	/** Pointer to the FSM's previous state. */
	DrivingState *previous_state;

protected:
	/** Pointer to the FSM's current state. */
	DrivingState *current_state;
};

#endif // UNB_FSMDRIVER_FSM_H
