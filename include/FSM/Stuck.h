#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "DrivingState.h"


/** @todo Should not be using global variables. FIX THIS!!!!! */
extern float STUCK_SPEED;
extern unsigned int MIN_RACED_DISTANCE;
extern unsigned int MAX_STUCK_TICKS;
extern unsigned int MAX_SLOW_SPEED_TICKS;


/** Implements the behavior for a driver that is stuck, THIS CLASS MUST BE
 * PROPERLY IMPLEMENTED! Singleton implementation aims to have one instance of
 * state for possibly many users, so slowSpeedTicks, elapsedTicks, trackInitialPos
 * cannot store information of a single user. @todo FIX THIS!!!!! */
class Stuck : public DrivingState {
public:
    /** Returns a pointer to the singleton for this state. */
    static Stuck *instance();

    /** Destructor. */
    ~Stuck();

    /* Inherited. */
    void enter(BaseDriver *, CarState &);

	/* Inherited. */
    CarControl drive(BaseDriver *, CarState &);

    /* Indicates whether the driver is stuck according to its perrception.
     * @param cs Driver's perception of the environment. */
	bool isStuck(CarState &cs);

private:
    /* Private functions (singleton pattern). */
    Stuck();
    Stuck(const Stuck &s);
    void operator=(const Stuck &s);


    unsigned int elapsedTicks;
    unsigned int slowSpeedTicks;
    float trackInitialPos;

    bool seemsStuck(CarState &cs);
    bool justStartedRace(CarState &cs);
	bool onRightWay(float trackPos, float angle);
	bool notStuckAnymore(float trackPos, float angle);
	bool hasBeenStuckLongEnough();

	float getSteer(float trackInitialPos, CarState &cs);
	float getInitialPos(CarState &cs);
};

#endif // FSMDRIVER_STATE_STUCK_H
