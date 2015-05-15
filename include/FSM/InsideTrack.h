#ifndef FSMDRIVER_STATE_TRACK_H
#define FSMDRIVER_STATE_TRACK_H

#include <cmath>
#include "FSM.h"
#include "Constants.h"


class FSMDriver;
/*! \class InsideTrack
 *  \brief InsideTrack State Class.
 *
 *  Class to treat the state where the car inside of the track. Most of the effort to enhance speed and surpass opponents is applied here.
 */
class InsideTrack : public DrivingState<FSMDriver> {
public:
    /** Create a pointer to the state to accomplish the singleton.
    */
    static InsideTrack *instance();
    /** Function to indicate that the drive started at insidetrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void enter(FSMDriver *driver);
    /** Function to indicate that the drive leave the insidetrack state. 
    * \param driver is a pointer of the object of the driver itself. 
    */
    void exit(FSMDriver *driver);
    /** Main function at state to drive the car.
    * \param driver is a pointer of the object of the driver itself,  
    * \param cs a data structure cointaining information from the car's sensors.
    */
    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs);
    /** Auxiliar function to obtain the gear analysing the car's rpm.
    */   
    int getGear(CarState &cs);
    //! Empty destructor
    ~InsideTrack();

private:
    InsideTrack();
    InsideTrack(InsideTrack const &);
    void operator=(InsideTrack const&);
    int currentGear;
    float distance, targetSpeed;

    bool shouldDecreaseGear(int currentGear, int rpm);
    inline bool runningOnLow(int rpm);
    inline bool runningUnderAverage(int rpm);
    inline bool runningOnHigh(int rpm);
    inline bool isLowGear(int gear);
    inline bool isHighGear(int gear);
    inline bool shouldIncreaseGear(int currentGear, int rpm);
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
