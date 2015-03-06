#ifndef FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include "FSM.h"

/******************************************************************************/
float STUCK_SPEED = 5;
unsigned int MIN_RACED_DISTANCE = 100;
unsigned int MAX_STUCK_TICKS = 300;
unsigned int MAX_SLOW_SPEED_TICKS=50;
/******************************************************************************/

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

    void enter(FSMDriver *driver, CarState &cs) {
        //cout << "Enter Stuck" << endl;
        elapsedTicks = 0;

    }

    void exit(FSMDriver *driver) {

        // cout << "Exit Stuck" << endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
		++elapsedTicks;
		trackInitialPos = getInitialPos(cs);
        if(notStuckAnymore(cs.getTrackPos(), cs.getAngle()) || hasBeenStuckLongEnough()){
			elapsedTicks = 0;
			slowSpeedTicks = 0;
			trackInitialPos = 0;
		}
        const float accel = 1, brake = 0, clutch = 0;
        const int gear = -1, focus = 0, meta = 0;
        float steer = getSteer(trackInitialPos, cs);

        return CarControl(accel, brake, gear, steer, clutch, focus, meta);
	}

    ~Stuck(){}

private:
	static inline bool seemsStuck(CarState &cs) {
		cs.getSpeedX()<STUCK_SPEED?slowSpeedTicks++:slowSpeedTicks=0;
		if(notStuckAnymore(cs.getTrackPos(), cs.getAngle())){
			slowSpeedTicks=0;
		}
		return (slowSpeedTicks>MAX_SLOW_SPEED_TICKS?1:0);
	    //return (abs(cs.getSpeedX()) <= STUCK_SPEED);
	}

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

	float getSteer(float trackInitialPos, CarState &cs){
        //return (trackInitialPos > 0 ? 1 : -1);
        if(abs(cs.getAngle()) > 1.557){// around 180 graus
        	return (trackInitialPos > 0 ? -1 : 1);
        }else{
        	return (trackInitialPos > 0 ? 1 : -1);
        }
        
	}
	float getInitialPos(CarState &cs){
		return (trackInitialPos==0?cs.getTrackPos():trackInitialPos);
	}

    unsigned int elapsedTicks;
    static unsigned int slowSpeedTicks;
    static float trackInitialPos;
};
unsigned int Stuck::slowSpeedTicks=0;
float Stuck::trackInitialPos=0;
#endif // FSMDRIVER_STATE_STUCK_H
