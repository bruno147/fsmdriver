#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#define PID_DT 0.02
  /** @todo verificar se este valor está correto. */

#define FINAL_SPEED 300 /** @todo Definir corretamente */
#define KP 0.1   /** @todo Definir corretamente */
#define KI 0.01  /** @todo Definir corretamente */
#define KD 0.005 /** @todo Definir corretamente */

#include "PID.h"
#include "SimpleParser.h"
#include "WrapperBaseDriver.h"
#include <cmath>

using namespace std;

//-----------------------------------------------------------------------------------------------------------------------
//Class Prototypes
class FsmDriver;
class State;

//-----------------------------------------------------------------------------------------------------------------------
//Abstract class for modeling behavior according to it's current state.

class State {
public:
    //Virtual method to drive according the state
    virtual CarControl execute(FsmDriver* fsmdriver)  = 0;

    //Virtual destructor
    virtual ~State(){}
};

//------------------------------------------------------------------------------------------------------------------------
//Curve State

class StateCurve : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver);
    StateCurve(){}
    ~StateCurve(){}
};

//------------------------------------------------------------------------------------------------------------------------
//Straight Line State

class StateStraightLine : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver);
    StateStraightLine();
    ~StateStraightLine(){}
private:
	float finalSpeed, desiredDirection;	/** Target Speed **/
    PIDController speedPID;
	
	int getGear(CarState & cs);
	float getSteering(CarState & cs);
	float getDistTrackAxis(CarState & cs);
	float getSpeed(CarState & cs);
};

//------------------------------------------------------------------------------------------------------------------------
//Out of the Track State

class StateOutOfTrack : public State {
public:
    virtual CarControl execute(FsmDriver *fsmdriver);
    ~StateOutOfTrack(){}
    StateOutOfTrack(){}
};

//------------------------------------------------------------------------------------------------------------------------
//Finite State Machine Driver

class FsmDriver : public WrapperBaseDriver {
private:
    State* _state;      //Pointer to current state
    CarState _cs;       //Sensorial information
public:
    // Print a shutdown message
    virtual void onShutdown();

    // Print a restart message
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    //Empty constructor and destructor
    FsmDriver(){}
    ~FsmDriver(){}

    //Getters and Setters methods.
    CarState &getCarState();
    void setCarState(CarState);
    void SetState(State* _newState);
    State* getState();

    //Checks whenever _state need to be changed.
    State* transition(CarState&);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
