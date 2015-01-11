#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include <cmath>
#include "FSM.h"


class FSMDriver;
class Stuck : public DrivingState<FSMDriver> {
public:
	//****************************************************
	static float STUCK_SPEED;
	static float MIN_RACED_DISTANCE;
	static float MAX_STUCK_TICKS;
	static float MAX_SLOW_SPEED_TICKS;
	//****************************************************

    static Stuck *instance();
    void enter(FSMDriver *driver, CarState &cs);
    void exit(FSMDriver *driver);
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);

	static inline bool isStuck(CarState &cs) {
	    return (seemsStuck(cs) && !justStartedRace(cs));
	}

    ~Stuck();

private:
    unsigned int elapsedTicks;
    static unsigned int slowSpeedTicks;
    static float trackInitialPos;
    
    Stuck();
    Stuck(Stuck const &);
    void operator=(Stuck const&);

	static bool seemsStuck(CarState &cs);
	float getSteer(float trackInitialPos, CarState &cs);
	float getInitialPos(CarState &cs);

	static inline bool justStartedRace(CarState &cs) {
	    return (cs.getDistRaced() <= MIN_RACED_DISTANCE); 
	}
	static inline bool onRightWay(float trackPos, float angle) {
	    return (((trackPos < 0) && (angle > -1.57) && (angle < 0)) ||
	            ((trackPos > 0) && (angle < 1.57 ) && (angle > 0)) ||
	            ((trackPos > 1) && (angle > 0))||
	            ((trackPos < -1) && (angle < 0)));
	}
	/* @todo give this test (and the previous ones) with a meaningful name... */
	static inline bool notStuckAnymore(float trackPos, float angle) {
		return (onRightWay(trackPos, angle));
	}
	inline bool hasBeenStuckLongEnough() {
		return (elapsedTicks >= MAX_STUCK_TICKS);
	}
};

#endif // FSMDRIVER_STATE_STUCK_H
