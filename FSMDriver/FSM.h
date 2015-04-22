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
/**The DrivingFSM class contein the function to change states and variable to indicate the current and the previous states.*/
class DrivingFSM {
public:
	DrivingFSM(Driver *o) : owner(o), previous_state(nullptr), current_state(nullptr) {
		assert(owner);
	}

	virtual ~DrivingFSM(){}
/**Function to change states it modify the variables current_state and previous_state according transition.*/
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
	DrivingState<Driver> *previous_state;
	
protected:
	DrivingState<Driver> *current_state;
};

#endif // FSMDRIVER_FSM_H
