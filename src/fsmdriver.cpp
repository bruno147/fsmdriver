#include "fsmdriver.h"

//-------------------------------------------------------------------------------------------------------------------
FsmDriver::FsmDriver() {

}

void FsmDriver::ChangeState(State *_newState) {
    delete _state;
    _state = _newState;
}

string FsmDriver::drive(string sensors) {
    CarState cs(sensors);
    this->ChangeState(transition(cs));
    return (_state->execute(this));
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
