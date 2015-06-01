#ifndef FSMDRIVER3_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include <cmath>
#include "FSM.h"


class FSMDriver3;
/*! \class Stuck
 * \brief Stuck State Class.
 *
 * Class to treat stuck state when the car is stop or with low speed, it usually happen at track section with high curvature.
 */
class Stuck : public DrivingState<FSMDriver3> {
public:
    /** Constructor
     * 
     * \param STUCK_SPEED
     * \param MIN_RACED_DISTANCE
     * \param MAX_STUCK_TICKS
     * \param MAX_SLOW_SPEED_TICKS
     */
    Stuck(float _ss = 5.0, int _mrd = 100, int _mst = 300, int _msst = 50);
    Stuck(Stuck const &);
    void operator=(Stuck const&);
    static bool isStuck(CarState &cs);
    /** Main function at state to drive the car.
    * /param driver is a pointer of the object of the driver itself,  
    * cs a data structure cointaining information from the car's sensors.
    */
    virtual CarControl drive(FSMDriver3 *fsmdriver3, CarState &cs);
    /** Auxiliar function to set class parameters
     * 
     * \param STUCK_SPEED
     * \param MIN_RACED_DISTANCE
     * \param MAX_STUCK_TICKS
     * \param MAX_SLOW_SPEED_TICKS
     */
    void setParameters(float, int, int, int);
    ~Stuck();

private:
    //! Parameters
    static float STUCK_SPEED;
    static unsigned int MIN_RACED_DISTANCE;
    static unsigned int MAX_STUCK_TICKS;
    static unsigned int MAX_SLOW_SPEED_TICKS;

    unsigned int elapsedTicks;
    static unsigned int slowSpeedTicks;
    static float trackInitialPos;

	float getSteer(float trackInitialPos, CarState &cs);
	float getInitialPos(CarState &cs);

	static bool seemsStuck(CarState &cs);
    static bool justStartedRace(CarState &cs);
    static bool onRightWay(float trackPos, float angle);
    static bool notStuckAnymore(float trackPos, float angle);
    bool hasBeenStuckLongEnough();
};

#endif // FSMDRIVER3_STATE_STUCK_H
