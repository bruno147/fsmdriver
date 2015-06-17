#include "FSMDriver3.h"
#include <vector>



/******************************************************************************/
#define NUM_SENSORS 19
/******************************************************************************/

int signum(float n) {
    if (n < 0) return -1;
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//FSMDriver3 Class

/**
*FSMDriver3 Constructor: it initilize at straightline state in the begining of the race, here the parameters are set with fixed values.
*/
FSMDriver3::FSMDriver3() {
    change_to(&insideTrack);
}
/**FSMDriver3 Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver3 can be used together with Genetic Algorithm using this function.
*/
FSMDriver3::FSMDriver3(int argc, char** argv) {
    change_to(&insideTrack);
}

void FSMDriver3::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FSMDriver3::onShutdown() {
    cout << "End of race!" << endl;
}

void FSMDriver3::init(float *angles){
    for (int i = 0; i < NUM_SENSORS; ++i)
        angles[i]=signum((i*1.0/3)-3)*exp(-(0.5)*powf((((i+9)%18)*1.0/3)-3, 2))*90;
}
/**The transition choose the most fitted state at the moment of the race. Note that the transition move to each state with only one pointer to each of than, what is called singleton.*/
void FSMDriver3::transition(CarState &cs) {
    DrivingState *state = current_state;

    if(stuck.isStuck(cs)) {
        state = &stuck;
    } else {
        if (cs.getTrack(1) > 0)
            state = &insideTrack;
        else
            state = &outOfTrack;
    }

    if (current_state != state) change_to(state);
}

FSMDriver3::~FSMDriver3() {
}
