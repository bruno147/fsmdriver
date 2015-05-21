/**  @file: DrivingFSM.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#ifndef UNB_FSMDRIVER_FSM_H
#define UNB_FSMDRIVER_FSM_H

#include "DrivingState.h"

/** Implements a Finite State Machine. */
class DrivingFSM {
public:
    /** The constructor.
     * @param driver Pointer to the driver who owns the FSM instance. */
    DrivingFSM(BaseDriver *driver) : owner(driver),
                                     previous_state(nullptr),
                                     current_state(nullptr) {
        assert(owner);
    }

    /** Destructor. */
    virtual ~DrivingFSM() {}

    /** Sets the FSM's current state.
     * @param new_state The state to change to. */
    void change_to(DrivingState *new_state) {
        if(new_state != current_state) {
            assert(new_state);

            previous_state = current_state;

            if(current_state)
                current_state->exit(owner);
            current_state = new_state;

            current_state->enter(owner);
        }
    }

    /** Reverts the FSM's current state to its previous instance. */
    void revert_state() {
        change_to(previous_state);
    }

    /** Decides the actions to take according the perception of the environment.
     * @param cs Driver's perception of the environment.
     * @return The driver's actions. */
    virtual CarControl update(CarState &cs) {
        return current_state->drive(owner, cs);
    }

    /** Indicates if the given state is the current state. */
    bool isCurrentState(DrivingState *state) {
        return (state == current_state);
    }

private:
    /** Driver that owns the FSM. */
    BaseDriver *owner;

    /** The state the FSM was before changing to current_state. */
    DrivingState *previous_state;

protected:
    /** The state the FSM is in. */
    DrivingState *current_state;
};

#endif // UNB_FSMDRIVER_FSM_H
