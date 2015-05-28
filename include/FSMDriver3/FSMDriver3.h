#ifndef FSMDRIVER3_H
#define FSMDRIVER3_H

#include <vector>

#include "WrapperBaseDriver.h"
#include "InsideTrack.h"
#include "OutOfTrack.h"
#include "Stuck.h"
#include "FSM.h"

/*! \class FSMDriver3
*   \brief The driver itself.
*   
*   This class defines the driver based on a FSM.
*
*   Please note that this documentation provide information about the espefic files of the newFSM driver,
*   the Loiacono's files(at src and include folder) have not been documented by us, for that reason the 
*   Doxygen does not generate these files documentation, more information can be found at the own comments
*   of the code. 
*/

class FSMDriver3 : public WrapperBaseDriver, public DrivingFSM<FSMDriver3> {
private:
    //! Actuators values.
    float accel, brake, steer;
    int gear;

    //! States.
    InsideTrack* insideTrack;
    OutOfTrack* outOfTrack;
    Stuck* stuck;

public:
    //! Called when the driver finishes the race. 
    virtual void onShutdown();
    //! Called when TORCS asks a race restart.
    virtual void onRestart();

    //! Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);
    //! Empty constructor.
    FSMDriver3();
    //! Construct from parameters.
    FSMDriver3(int, char**);
    //! Empty destructor
    virtual ~FSMDriver3();
    //! Transitions between states.
    /*!  
    *   This method decides whenever the current state does not fit with
    *   the car status and needs to be changed.The transition choose the most fitted state at the moment of the race. 
    *	Note that the transition move to each state with only one pointer to each of than, what is called singleton.
    *   \param cs a data structure cointaining information from the car's sensors.
    */
    void transition(CarState &cs);

    //! Main driving function.
    /*! \param cs a data structure cointaining information from the car's sensors.
    *   \return The data structure cointaining values for the car's actuators.
    */
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDriver3_H
