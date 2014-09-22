#ifndef STATE_H
#define STATE_H

#define PID_DT 0.02
  /** @todo verificar se este valor está correto. */

#define FINAL_SPEED 300 /** @todo Definir corretamente */
#define KP 0.1   /** @todo Definir corretamente */
#define KI 0.01  /** @todo Definir corretamente */
#define KD 0.005 /** @todo Definir corretamente */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "PID.h"
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
    virtual string execute(FsmDriver* fsmdriver, CarState )  = 0;
};

//------------------------------------------------------------------------------------------------------------------------
//

class StateCurve : public State {
public:
    virtual string execute(FsmDriver *fsmdriver, CarState );
};

//------------------------------------------------------------------------------------------------------------------------
//

class StateStraightLine : public State {
public:
    virtual string execute(FsmDriver *fsmdriver, CarState cs);
    StateStraightLine();

private:
	float finalSpeed, desiredDirection;	/** Target Speed **/
	PIDController speedPID;
	
	int getGear(CarState & cs);
	float getSteering(CarState & cs);
	float getDistTrackAxis(CarState & cs);
	float getSpeed(CarState & cs);
};

//------------------------------------------------------------------------------------------------------------------------
//

class StateOutOfTrack : public State {
public:
    virtual string execute(FsmDriver *fsmdriver, CarState );
};

#endif // STATE_H
