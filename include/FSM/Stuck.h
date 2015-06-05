#ifndef UNB_FSMDRIVER_STATE_STUCK_H
#define FSMDRIVER_STATE_STUCK_H

#include <cmath>
#include "FSM.h"

/**
 * Handles the driving when the car stuck. This usually means it is stopped or
 * with low speed, it usually happen at track section with high curvature.
 *
 * @todo proper description
 * @todo proper documentation
 */
class Stuck : public DrivingState {
public:
    /** Constructor.
     *
     * @param o a pointer to the driver that owns the state.
     * \param STUCK_SPEED
     * \param MIN_RACED_DISTANCE
     * \param MAX_STUCK_TICKS
     * \param MAX_SLOW_SPEED_TICKS
     */
    Stuck(FSMDriver *o, float _ss = 5.0, int _mrd = 100, int _mst = 300, int _msst = 50);
    // Stuck(Stuck const &);
    // void operator=(Stuck const&);


    /* Inherited documentation. */
    CarControl drive(CarState &);

    static bool isStuck(CarState &cs);
    /** Auxiliar function to set class parameters
     *
     * \param STUCK_SPEED
     * \param MIN_RACED_DISTANCE
     * \param MAX_STUCK_TICKS
     * \param MAX_SLOW_SPEED_TICKS
     */
    void setParameters(float, int, int, int);
    ~Stuck();

public:
    //! Parameters
    /** @todo documentar. Por que estáticos?
     * @todo deixar argumentos privados. */
    static float STUCK_SPEED;
    static unsigned int MIN_RACED_DISTANCE;
    static unsigned int MAX_STUCK_TICKS;
    static unsigned int MAX_SLOW_SPEED_TICKS;

private:
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

#endif // UNB_FSMDRIVER_STATE_STUCK_H
