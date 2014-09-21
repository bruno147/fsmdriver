#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "BaseDriver.h"
#include "CarState.h"
#include "CarControl.h"
#include "SimpleParser.h"
#include "WrapperBaseDriver.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------
//Prototypes
class FsmDriver;

//-----------------------------------------------------------------------------------------------------------------------
//Abstract class for modeling behavior according to it's current state.

class State {
public:
    virtual void drive(FsmDriver* fsmdriver)  = 0;
};

//------------------------------------------------------------------------------------------------------------------------
//

class StateCurve : public State {
public:
    void drive(FsmDriver *fsmdriver);
};

//------------------------------------------------------------------------------------------------------------------------
//

class StateStraightLine : public State {
public:
    void drive(FsmDriver *fsmdriver);

};

//------------------------------------------------------------------------------------------------------------------------
//

class StateOutOfTrack : public State {
public:
    void drive(FsmDriver *fsmdriver);
};

#endif // STATE_H
