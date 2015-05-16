#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "WrapperBaseDriver.h"
#include "FSM.h"
#include <bitset>

/*! \class FSMDriver
*   \brief The driver itself.
*   
*   This class defines the driver based on a FSM.
*   Please note that this documentation provide information about the espefic files of the newFSM driver,
*   the Loiacono's files(at src and include folder) have not been documented by us, for that reason the 
*   Doxygen does not generate these files documentation, more information can be found at the own comments
*   of the code. 
*/

class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
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

    FSMDriver();
    FSMDriver(int, char**);
    virtual ~FSMDriver(){}

    /** Transitions between states (if appropriate).*/
    void transition(CarState &);

    /**Main driving function.*/
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDriver_H
