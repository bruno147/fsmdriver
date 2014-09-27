#ifndef FSMDRIVER_STATE_H
#define FSMDRIVER_STATE_H

//FSMDriver class prototype
class FsmDriver;

class State {
public:
    //Virtual method to drive according the state
    virtual CarControl execute(FsmDriver* fsmdriver) = 0;

    //Virtual destructor
    virtual ~State(){}
};

#endif // FSMDRIVER_STATE_H
