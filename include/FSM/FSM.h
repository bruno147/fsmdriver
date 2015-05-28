#ifndef FSM_H
#define FSM_H

#include "CarControl.h"
#include "CarState.h"


/*! \class DrivingState
 *	\brief Abstract class that defines the driving state of the state machine.
 *
 *	The driving state defines wich driving policy should be choosen
 *  according to the car position in the track.
 */
template <class Driver>
class DrivingState {
public:
	//! The virtual destructor.
    virtual ~DrivingState(){}
    //! Defines the driving policy of the state.
    virtual CarControl drive(Driver *, CarState &) = 0;
    //! Initial function called by each state.
    virtual void enter(Driver *){}
    //! Final function called by each state.
    virtual void exit(Driver *){}
};

/*! \class DrivingFSM
*	\brief The actual state machine
*	
*	This is the Finite State Machine structure containing it's states
*	and owner values.
*/
template <class Driver>
class DrivingFSM {
public:
	//! The constructor.
	/*! It sets the initial FSM atributes.
	*/
	DrivingFSM(Driver *o) : owner(o), previous_state(nullptr), current_state(nullptr) {
		assert(owner);
	}
	//! An empty destructor.
	virtual ~DrivingFSM(){}
	//! This function allows the FSM to swap through states.
	/*!  \param s a new state.
	*/
	void change_to(DrivingState<Driver> *s) {
		assert(s);
		previous_state = current_state;
		// if(current_state) current_state->exit(owner);
		current_state = s;
		// current_state->enter(owner);
	}
	//! It allows the FSM to return to the previous state.
	void revert_state() {
		change_to(previous_state);
	}
	//! It calls the state's main function.
	/*! \param cs a data structure cointaining information from the car's sensors.
	*	\return The data structure cointaining values for the car's actuators.
	*/
	virtual CarControl update(CarState &cs) {
		return current_state->drive(owner, cs);
	}

private:
	//! Pointer to the FSM owner.
	Driver *owner;
	//! Pointer to the previous state.
	/*! Used for tracking the last state of the state machine.
	*/
	DrivingState<Driver> *previous_state;
	
protected:
	//! The current state.
	DrivingState<Driver> *current_state;
};

#endif // FSM_H
