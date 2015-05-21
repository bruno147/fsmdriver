#ifndef UNB_FSMDRIVER_FSMDRIVER_5_H
#define UNB_FSMDRIVER_FSMDRIVER_5_H

#include <bitset>

#include "FSMDriver.h"

extern float BASE_SPEED;

/** Defines a controller that uses a Finite State Machine with 5 states do model
 * its behavior. */
class FSMDriver5 : public FSMDriver {
private:
    float accel, brake, steer; //Actuators values
    int gear;
    int segment_id;

    int MAX_STRAIGHT_LINE_VAR;
    int MIN_STRAIGHT_LINE_VAR;
    int MAX_APPROACHING_CURVE_VAR;
    int MIN_APPROACHING_CURVE_VAR;

    float    binToFloat (string bits);
    unsigned int binToUsignedInt (string bits);

    std::string getArgument(int i, char** argv);


    float    parameters[22];/**Driver parameters,it can be fixed or set by Genetic Algorithm*/

public:
    virtual void onShutdown();
    virtual void onRestart();

    /** Initialization of the desired angles for the rangefinders*/
    virtual void init(float *angles);

    FSMDriver5();
    FSMDriver5(int, char**);
    virtual ~FSMDriver5(){}

    /** Transitions between states (if appropriate).*/
    void transition(CarState &);

    /**Main driving function.*/
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDriver5_H
