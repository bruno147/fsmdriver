#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "FSM.h"

const float STUCK_SPEED = 5;
const int MIN_RACED_DISTANCE = 100;
const int MAX_STUCK_TICKS = 300;

class FSMDriver;
class Stuck : public DrivingState<FSMDriver> {
public:
    static Stuck *instance() {
        static Stuck instance;
        return &instance;
    }

private:
    Stuck() : elapsedTicks(0) {}
    Stuck(Stuck const &);
    void operator=(Stuck const&);

public:
	static inline bool isStuck(CarState &cs) {
	    return (seemsStuck(cs) && !justStartedRace(cs));
	}

    void enter(FSMDriver *driver) {
        cout << "Enter Stuck" << endl;
        elapsedTicks = 0;
    }

    void exit(FSMDriver *driver) {
        cout << "Exit Stuck" << endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
		++elapsedTicks;

        if(notStuckAnymore(cs.getAngle(), cs.getTrackPos()) || hasBeenStuckLongEnough())
			elapsedTicks = 0;

        const float accel = 1, brake = 0, clutch = 0;
        const int gear = -1, focus = 0, meta = 0;
        float steer = getSteer(cs);

        return CarControl(accel, brake, gear, steer, clutch, focus, meta);
	}

    ~Stuck(){}

private:
	static inline bool seemsStuck(CarState &cs) {
	    return (abs(cs.getSpeedX()) <= STUCK_SPEED);
	}

	static inline bool justStartedRace(CarState &cs) {
	    return (cs.getDistRaced() <= MIN_RACED_DISTANCE); 
	}

	inline bool outOfTrackLeft(float trackPos, float angle) {
	    return ((trackPos > 1) && (angle > 0));
	}

	inline bool outOfTrackRight(float trackPos, float angle) {
	    return ((trackPos < -1) && (angle < 0));
	}

	inline bool outOfTrack(float trackPos, float angle) {
	    return (outOfTrackLeft(trackPos, angle) || outOfTrackRight(trackPos, angle));
	}

	inline bool onTrack(float trackPos, float angle) {
	    return (((trackPos < 0) && (angle < 0)) ||
	            ((trackPos > -1) && (trackPos < 0) && (angle < 0)) ||
	            ((trackPos > 0) && (trackPos < 1) && (angle > 0)));
	}

	/* @todo give this test (and the previous ones) with a meaningful name... */
	inline bool notStuckAnymore(float trackPos, float angle) {
		return (outOfTrack(trackPos, angle) || onTrack(trackPos, angle));
	}

	inline bool hasBeenStuckLongEnough() {
		return (elapsedTicks >= MAX_STUCK_TICKS);
	}

	float getSteer(CarState & cs){
        return (cs.getTrackPos() > 0 ? 1 : -1);
	}

    unsigned int elapsedTicks;
};
#endif // FSMDRIVER_STATE_STUCK_H
