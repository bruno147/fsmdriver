#include "FSMDriver3.h"
#include "InsideTrack.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>

/******************************************************************************/
#define NUM_SENSORS 19
/******************************************************************************/

/*******************************************************************************
 * Helper functions.
*******************************************************************************/
inline
int signum(float n) {
    return (n < 0 ?  -1 : 1);
}
/******************************************************************************/


//-------------------------------------------------------------------------------------------------------------------
//FSMDriver Class

/**
*FSMDriver Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.
*/
FSMDriver3::FSMDriver3() {
    fsm.change_to(InsideTrack::instance());
}

// FSMDriver3::FSMDriver3(int argc, char** argv) {
//     fsm.change_to(InsideTrack::instance());
// }

FSMDriver3::~FSMDriver3() {}

CarControl FSMDriver3::wDrive(CarState cs) {
    transition(cs);
    return fsm.update(cs);
}

void FSMDriver3::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver3::onShutdown() {
    cout << "End of race!" << endl;
}

/**  Initialization of the desired angles for the rangefinders.
 * @param angles @todo document this. */
void FSMDriver3::init(float *angles) {
    /** @todo make code clearer. */
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i]=signum((i*1.0/3)-3)*exp(-(0.5)*powf((((i+9)%18)*1.0/3)-3, 2))*90;
}

/**This method decides whenever the current state does not fit with
 *   the car status and needs to be changed.The transition choose the most fitted state at the moment of the race.
 *   Note that the transition move to each state with only one pointer to each of than, what is called singleton.
 *   \param cs a data structure cointaining information from the car's sensors.
 *
 * The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton. */
void FSMDriver3::transition(CarState &cs) {
    DrivingState *state = Stuck::instance();

    if(!((Stuck *)state)->isStuck(cs)) {
        if (cs.getTrack(1) > 0) /** @todo make this test clearer. */
            state = InsideTrack::instance();
        else
            state = OutOfTrack::instance();
    }

    fsm.change_to(state);
}

