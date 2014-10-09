#ifndef FSMDRIVER_FSM_H
#define FSMDRIVER_FSM_H

#include "CarControl.h"
#include "CarState.h"

template <class Driver>
class DrivingState {
public:
    virtual ~DrivingState(){}

    virtual CarControl drive(Driver *, CarState &) = 0;
    virtual void enter(Driver *){}
    virtual void exit(Driver *){}
};	

template <class Driver>
class DrivingFSM {
public:
	DrivingFSM(Driver *o) : owner(o), current_state(nullptr), previous_state(nullptr) {
		assert(owner);
	}

	virtual ~DrivingFSM(){}

	void change_to(DrivingState<Driver> *s) {
		assert(s);

		previous_state = current_state;
		if(current_state) current_state->exit(owner);
		current_state = s;
		current_state->enter(owner);
	}

	void revert_state() {
		change_to(previous_state);
	}

	virtual CarControl update(CarState &cs) {
		return current_state->drive(owner, cs);
	}

private:
	Driver *owner;
	DrivingState<Driver> *current_state, *previous_state;
};

#endif // FSMDRIVER_FSM_H
