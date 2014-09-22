#include "state.h"

//-----------------------------------------------------------------------------------------------------------------
//StateCurve Class
string StateCurve::execute(FsmDriver *fsmdriver, CarState string) {
    /*
     *
     *
     * INSERT CRESTANI'S CODE HERE.
     *
     *
     * */
}

//-----------------------------------------------------------------------------------------------------------------
//StateStraigtLine Class

int StateStraightLine::getGear(CarState & cs) {
    int current_gear = cs.getGear();
    if(!current_gear) return 1;

    // if(current_gear == 1 || current_gear == 2)   std::cout << "Current Gear = " << current_gear <<  " RPM = " << cs.getRpm() << std::endl;

    if(current_gear > 1 && current_gear < 4 && cs.getRpm() < 1500)
        return(current_gear - 1);

    if(current_gear < 2 && cs.getRpm() > 8000)
        return(current_gear + 1);

    if(current_gear >= 2 && cs.getRpm() > 8500)
        return(current_gear + 1);

    if(current_gear >= 4 && cs.getRpm() < 4000)
        return(current_gear - 1);

    return current_gear;
}

float StateStraightLine::getSteering(CarState & cs) {
    // based on Loiacono's SimpleDriver

    const float
      steerLock = 0.366519;
    float
      targetAngle = (cs.getAngle() - cs.getTrackPos() * 0.5) / steerLock;

    // normalize steering
    if(targetAngle < -1)
        targetAngle = -1;
    else if(targetAngle > 1)
        targetAngle = 1;

    return targetAngle;
}

float StateStraightLine::getDistTrackAxis(CarState & cs) {
    return cs.getTrackPos();
}

float StateStraightLine::getSpeed(CarState & cs) {
    return sqrt(pow(cs.getSpeedX(), 2) + pow(cs.getSpeedY(), 2));
}

string StateStraightLine::execute(FsmDriver *fsmdriver, CarState cs) {
    // CarState cs(sensors);

    // static int flag = 0;

    float brake = 0, clutch = 0;

    float accel = speedPID.output(finalSpeed, StateStraightLine::getSpeed(cs), PID_DT);

    // float steer = steeringPID.output(desiredDirection, getDistTrackAxis(cs), PID_DT);
    float steer = StateStraightLine::getSteering(cs);

    int gear = StateStraightLine::getGear(cs), focus = 0, meta = 0;

    std::cout << "accel = " << accel << " gear = " << gear << " steer = " << steer << " fuel = " << cs.getFuel() << std::endl;  

    CarControl cc(accel, brake, gear, steer, clutch, focus, meta);

    // std::cout << getSpeed(cs) << std::endl;
    // if(getSpeed(cs) >= 297 && flag == 0)
    // {
    //     // t = clock() - t;
    //     std::cout << "Velocidade Limite em = " << ((float)(clock() - t))/(CLOCKS_PER_SEC) << " segundos" << std::endl;
    //     flag = 1;
    // }

    return cc.toString();
}

StateStraightLine::StateStraightLine() : speedPID(KP, KI, KD) {
    finalSpeed = FINAL_SPEED;
}

//-----------------------------------------------------------------------------------------------------------------
//StateCurve Class

string StateOutOfTrack::execute(FsmDriver *fsmdriver, CarState ) {
    /*
     *
     *
     * INSERT SOUSA'S CODE HERE.
     *
     *
     * */
}
//-----------------------------------------------------------------------------------------------------------------
