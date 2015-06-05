#ifndef UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H
#define UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H

#include <cmath>
#include "FSM.h"

/**
 * Handles the driving when the car is outside track limits.
 *
 * @todo proper description
 * @todo proper documentation
 */
class OutOfTrack : public DrivingState {
public:
    /** Constructor.
     *
     * @param o a pointer to the driver that owns the state.
     * \param MAX_SKIDDING
     * \param NEGATIVE_ACCEL_PERCENT
     * \param VELOCITY_GEAR_4
     * \param VELOCITY_GEAR_3
     * \param VELOCITY_GEAR_2
     * \param MAX_RETURN_ANGLE
     * \param MIN_RETURN_ANGLE
     */
    OutOfTrack(FSMDriver *o,
               float _ms = 3, float _nap = 0.1, int _vg4 = 90,
               int _vg3 = 70, int _vg2 = 40, float _maxra = 0.7,
               float _minra = 0.5);
    //! Construct from parameters.
    // OutOfTrack(OutOfTrack const &);
    // void operator=(OutOfTrack const&);


    /* Inherited documentation. */
    CarControl drive(CarState &);

    /** Auxiliar function to set class parameters
     *
     * \param MAX_SKIDDING
     * \param NEGATIVE_ACCEL_PERCENT
     * \param VELOCITY_GEAR_4
     * \param VELOCITY_GEAR_3
     * \param VELOCITY_GEAR_2
     * \param MAX_RETURN_ANGLE
     * \param MIN_RETURN_ANGLE
     */
    void setParameters(float, float, int, int, int, float, float);
    //! Empty destructor
    ~OutOfTrack();

public:
    //! Parameters
    /** @todo documentar
     * @todo deixar argumentos privados. */
    float MAX_SKIDDING;
    float NEGATIVE_ACCEL_PERCENT;
    int VELOCITY_GEAR_4;
    int VELOCITY_GEAR_3;
    int VELOCITY_GEAR_2;
    float MAX_RETURN_ANGLE;
    float MIN_RETURN_ANGLE;

private:
    float getBrake(CarState &cs);
    float getAccel(CarState &cs);
    int getGear(CarState &cs);
    float getSteer(CarState &cs);
};

#endif // UNB_FSMDRIVER_STATE_OUT_OF_TRACK_H
