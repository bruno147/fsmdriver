#include "fsmdriver.h"

//-------------------------------------------------------------------------------------------------------------------
FsmDriver::FsmDriver() {

}

void FsmDriver::ChangeState(State *_newState) {
    delete _state;
    _state = _newState;
}

void FsmDriver::drive(CarState &cs) {
    this->ChangeState(transition(cs));
    _state->drive(this);
}

State* FsmDriver::transition(CarState &cs) {
    /*
     *
     *
     * INSERT GALI'S CODE HERE.
     *
     *
     * */
}
//--------------------------------------------------------------------------------------------------------------------
