#ifndef UNB_FSMDRIVER_STATE_INSIDE_TRACK_H
#define UNB_FSMDRIVER_STATE_INSIDE_TRACK_H

#include <cmath>
#include "FSM.h"

/**
 * Handles the driving when the car is within track limits.
 *
 * @todo proper description
 * @todo proper documentation
 */
class InsideTrack : public DrivingState {
public:
    /* Constructor
     *
     * @param o a pointer to the driver that owns the state.
     * \param START_GEAR
     * \param LOW_GEAR_LIMIT
     * \param LOW_RPM
     * \param AVERAGE_RPM
     * \param HIGH_RPM
     * \param BASE_SPEED
     * \param SPEED_FACTOR
     */
    InsideTrack(FSMDriver *o,
                int _sg = 1, int _lgl = 4, int _lrpm = 1500,
                int _arpm = 4000, int _hrpm = 9000, float _bs = 83,
                float _sf = 1.4);
    // InsideTrack(InsideTrack const &);
    // void operator=(InsideTrack const&);


    /* Inherited documentation. */
    CarControl drive(CarState &);

    /** Auxiliar function to obtain the gear analysing the car's rpm.
    */
    int getGear(CarState &cs);
    /** Auxiliar function to set class parameters
     *
     * \param START_GEAR
     * \param LOW_GEAR_LIMIT
     * \param LOW_RPM
     * \param AVERAGE_RPM
     * \param HIGH_RPM
     * \param BASE_SPEED
     * \param SPEED_FACTOR
     */
    void setParameters(int, int, int, int, int, float, float);
    //! Empty destructor
    ~InsideTrack();

private:
    //! Parameters
    int START_GEAR;
    int LOW_GEAR_LIMIT;
    int LOW_RPM;
    int AVERAGE_RPM;
    int HIGH_RPM;
    float BASE_SPEED;
    float SPEED_FACTOR;


    int currentGear;
    float distance, targetSpeed;

    bool shouldDecreaseGear(int currentGear, int rpm);
    bool runningOnLow(int rpm);
    bool runningUnderAverage(int rpm);
    bool runningOnHigh(int rpm);
    bool isLowGear(int gear);
    bool isHighGear(int gear);
    bool shouldIncreaseGear(int currentGear, int rpm);
    float getAccel(CarState &cs);
    void setTargetSpeed(CarState &cs);
    /** isFacingWrongWay verify if the car is driving the right path, once it is possible
    * that the car collide and turn to the opposite way.
    * /param cs a data structure cointaining information from the car's sensors.
    */
    bool isFacingWrongWay(CarState &cs);
    float getBrake(CarState cs);
    float findFarthestDirection(CarState &cs);
    float normalizeSteer(float angle);
    float getSteer(CarState &cs);
};

#endif // FSMDRIVER_STATE_INSIDETRACK_H
