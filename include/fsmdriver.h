#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "state.h"

//-----------------------------------------------------------------------------------------------------------------------
//Finite State Machine Driver

class FsmDriver : public WrapperBaseDriver {
private:
    State* _state;
public:
    FsmDriver();
    void ChangeState(State* _newState);
    State* transition(CarState&);
    void drive(CarState &cs);
};

//-----------------------------------------------------------------------------------------------------------------------
#endif // FSMDRIVER_H
