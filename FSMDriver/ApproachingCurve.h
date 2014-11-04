#ifndef APPROACHINGCURVE_H
#define APPROACHINGCURVE_H


#include "FSM.h"

class FSMDriver;

class ApproachingCurve : public DrivingState<FSMDriver> {
public:
    ~ApproachingCurve(){}
    static ApproachingCurve* instance() {
        static ApproachingCurve instance;
        return &instance;
    }

    void enter(FSMDriver *driver) {
        std::cout << "Enter ApproachingCurve" << std::endl;
        this->setValues(driver->cs);
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit ApproachingCurve" << std::endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
        const int focus = 0, meta = 0;
        const float clutch = 0;
        return CarControl(getAccel(cs), getBrake(cs), getGear(cs), getSteering(cs), clutch, focus, meta);
    }

private:
    const float MAX_STEERING, TARGET_POS, BASE_SPEED;
    float rSensor, cSensor, lSensor, targetSpeed;
    ApproachingCurve() :
        MAX_STEERING(0.12), TARGET_POS(0.6), BASE_SPEED(80) {}

    void setValues(CarState &cs) {
        if (cs.getFocus(2) == -1) {                     //Focus sensors are available only once per second
            std::cout << "FOCUS ERROR!" << std::endl;
            rSensor = cs.getTrack(10);                  //Use track sensors
            cSensor = cs.getTrack(9);
            lSensor = cs.getTrack(8);
        }
        else {
            rSensor = cs.getFocus(3);                   //Use focus sensors
            cSensor = cs.getFocus(2);
            lSensor = cs.getFocus(1);
        }
        targetSpeed = BASE_SPEED + 5000/fabs(lSensor - rSensor);
    }

    int getGear(CarState & cs) {
        int current_gear = cs.getGear();
        if(!current_gear) return 1;

        if(current_gear > 1 && current_gear < 4 && cs.getRpm() < 1500)
            return(current_gear - 1);

        if(current_gear < 2 && cs.getRpm() > 9500)
            return(current_gear + 1);

        if(current_gear >= 2 && cs.getRpm() > 9500)
            return(current_gear + 1);

        if(current_gear >= 4 && cs.getRpm() < 4000)
            return(current_gear - 1);

        return current_gear;
    }

    float getAccel(CarState cs) {
        if (cs.getSpeedX() > targetSpeed)
            return 0;
        else
            return 1;
    }

    float getSteering(CarState cs) {
        float a = cs.getAngle(), p = cs.getTrackPos();
        if (rSensor > lSensor) {                            //Approaching a turn to the right
            if (p < TARGET_POS)                             //Move to target position
                return MAX_STEERING-a;
            else                                            //Stay parallel to track axis
                return a;
        }
        if (lSensor > rSensor) {                            //Approaching a turn to the left
            if (p > -TARGET_POS)
                return -MAX_STEERING+a;
            else
                return a;
        }
        return 0;
    }

    float getBrake(CarState &cs) {
        if (cs.getSpeedX() < targetSpeed)
            return 0;
        else
            return 0.02*(cs.getSpeedX() - targetSpeed);
    }

};



#endif // APPROACHINGCURVE_H
