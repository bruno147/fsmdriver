#include "FSMDriver.h"
#include "InsideTrack.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>



/******************************************************************************/
#define NUM_SENSORS 19
/******************************************************************************/


//-------------------------------------------------------------------------------------------------------------------
//FSMDriver Class

/**
*FSMDriver Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.  
*/
FSMDriver::FSMDriver() : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(InsideTrack::instance());
}
/**FSMDriver Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver can be used together with Genetic Algorithm using this function.
*/
FSMDriver::FSMDriver(int argc, char** argv) : DrivingFSM<FSMDriver>(this), accel(0),brake(0),steer(0),gear(0) {
    change_to(InsideTrack::instance());
}

CarControl FSMDriver::wDrive(CarState cs) {
    transition(cs);
    return update(cs);
}

void FSMDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver::onShutdown() {
    cout << "End of race!" << endl;
}

int signum(float n) {
    if (n < 0) return -1;
    return 1;
}

void FSMDriver::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i]=signum((i*1.0/3)-3)*exp(-(0.5)*powf((((i+9)%18)*1.0/3)-3, 2))*90;
}
/**The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
void FSMDriver::transition(CarState &cs) {
    DrivingState<FSMDriver> *state = current_state;

    if(Stuck::isStuck(cs)) {
        state = Stuck::instance();
    } else {
        if (cs.getTrack(1) > 0) 
            state = InsideTrack::instance();
        else
            state = OutOfTrack::instance();
    }

    if (current_state != state) change_to(state);
}

