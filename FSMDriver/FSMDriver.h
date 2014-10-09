#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#define PID_DT 0.02
  /** @todo verificar se este valor está correto. */

#define FINAL_SPEED 300 /** @todo Definir corretamente */
#define KP 0.1   /** @todo Definir corretamente */
#define KI 0.01  /** @todo Definir corretamente */
#define KD 0.005 /** @todo Definir corretamente */

#include "PID.h"
#include "WrapperBaseDriver.h"
#include <cmath>

#include "FSM.h"

//------------------------------------------------------------------------------------------------------------------------
//Finite State Machine Driver

class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
private:
    float accel, brake, steer;          //Actuators values
    int gear;

    static const float  LEFT_EDGE;
    static const float  RIGHT_EDGE;
    static const float  MAX_SPEED_DIST;
    static const float  MAX_STR_ANGLE;
    static const float  MIN_STR_ANGLE;
    static const int    STUCK_TICKS;
public:
    // Print a shutdown message
    virtual void onShutdown();

    // Print a restart message
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    //Empty constructor and destructor
    FSMDriver();
    virtual ~FSMDriver(){}

    //Checks whenever _state need to be changed.
    void transition(CarState &);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
