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

#include "State.h"

//------------------------------------------------------------------------------------------------------------------------
//Finite State Machine Driver

class FsmDriver : public WrapperBaseDriver {
private:
    State* _state;                      //Pointer to current state
    CarState _cs;                       //Sensorial information
    float accel, brake, steer;          //Actuators values
    int gear;
public:
    // Print a shutdown message
    virtual void onShutdown();

    // Print a restart message
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    //Empty constructor and destructor
    FsmDriver();
    ~FsmDriver(){}

    //Getters and Setters methods.
    CarState &getCarState();
    void setCarState(CarState);
    void SetState(State* _newState);
    State* getState();
    float getAccel();
    void setAccel(float acel);
    float getBrake();
    void setBrake(float brake);
    float getSteer();
    void setSteer(float steer);
    int getGear();
    void setGear(int gear);

    //Checks whenever _state need to be changed.
    State* transition(CarState&);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
