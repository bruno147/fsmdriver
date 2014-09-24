#include "FsmDriver.h"

//-------------------------------------------------------------------------------------------------------------------
//FsmDriver Class

FsmDriver::FsmDriver() {
    this->accel = 0;
    this->brake = 0;
    this->steer = 0;
    this->gear = 0;
}

CarState& FsmDriver::getCarState() {
    return this->_cs;
}

void FsmDriver::setCarState(CarState cs) {
    this->_cs = cs;
}

State* FsmDriver::getState() {
    return this->_state;
}

void FsmDriver::SetState(State *_newState) {
    delete this->_state;
    this->_state = _newState;
}

float FsmDriver::getAccel() {
    return this->accel;
}

void FsmDriver::setAccel(float accel) {
    this->accel = accel;
}

float FsmDriver::getBrake() {
    return this->brake;
}

void FsmDriver::setBrake(float brake) {
    this->brake = brake;
}

float FsmDriver::getSteer() {
    return this->steer;
}

void FsmDriver::setSteer(float steer) {
    this->steer = steer;
}

int FsmDriver::getGear() {
    return this->gear;
}

void FsmDriver::setGear(int gear) {
    this->gear = gear;
}

CarControl FsmDriver::wDrive(CarState cs) {
    this->setCarState(cs);
    this->SetState(transition(this->getCarState()));
    return (this->getState())->execute(this);
}

void FsmDriver::onRestart() {
    cout << "Restarting the race!" << endl;
}

void FsmDriver::onShutdown() {
    cout << "End of race!" << endl;
}

void FsmDriver::init(float *angles){
    for (int i = 0; i < 19; ++i)
        angles[i]=-90+i*10;
}

State* FsmDriver::transition(CarState &cs) {
    /*
     *
     *
     * INSERT GALI'S CODE HERE.
     *
     *
     * */
    State* p = new StateStraightLine();
    return p;
}

//-----------------------------------------------------------------------------------------------------------------
//StateCurve Class
CarControl StateCurve::execute(FsmDriver *fsmdriver) {
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

CarControl StateStraightLine::execute(FsmDriver *fsmdriver) {
    CarState& cs = fsmdriver->getCarState();
    // static int flag = 0;

    // float accel = speedPID.output(finalSpeed, StateStraightLine::getSpeed(cs), PID_DT);

    fsmdriver->setAccel( speedPID.output(finalSpeed, StateStraightLine::getSpeed(cs), PID_DT) );

    // float steer = steeringPID.output(desiredDirection, getDistTrackAxis(cs), PID_DT);
    // float steer = StateStraightLine::getSteering(cs);

    fsmdriver->setSteer( StateStraightLine::getSteering(cs) );

    // int gear = StateStraightLine::getGear(cs);

    fsmdriver->setGear( StateStraightLine::getGear(cs) );

    std::cout << "accel = " << fsmdriver->getAccel() << " gear = " << fsmdriver->getGear() << " steer = " << fsmdriver->getSteer() << " fuel = " << cs.getFuel() << std::endl;

    CarControl cc(fsmdriver->getAccel(), 0, fsmdriver->getGear(), fsmdriver->getSteer(), 0, 0, 0);

    return cc;
}

StateStraightLine::StateStraightLine() : speedPID(KP, KI, KD) {
    finalSpeed = FINAL_SPEED;
}

//-----------------------------------------------------------------------------------------------------------------
//StateOutOfTrack Class
float StateOutOfTrack::getBrake(CarState & cs){
    if(abs(cs.getSpeedY())>3){
        return 0.1;
    }else{
        return 0;
    }
}
float StateOutOfTrack::getAccel(CarState & cs){
    return(1-abs(cs.getSpeedY())*0.1);        //can be negative, need to fix
}

int StateOutOfTrack::getGear(CarState & cs){
    if(cs.getSpeedX()>90){
        return cs.getGear();
    }else if(cs.getSpeedX()>70){
        return 3;
    }else if(cs.getSpeedX()>40){
        return 2;
    }else{
        return 1;
    }
}
float StateOutOfTrack::getSteer(CarState & cs){
    if(cs.getTrackPos()>0){
        if(cs.getAngle()>0.7){
            return 1;
        }else if(cs.getAngle()<0.5){
            return -1;
        }
    }else{
        if(cs.getAngle()<-0.7){
            return -1;
        }else if(cs.getAngle()<0.5){
            return 1;
        }
    }
}

CarControl StateOutOfTrack::execute(FsmDriver *fsmdriver) {
    CarState& cs = fsmdriver->getCarState();
    CarControl cc(this->getAccel(cs), this->getBrake(cs), this->getGear(cs), this->getSteer(cs), 0, 0, 0);
    return cc;
}
//-----------------------------------------------------------------------------------------------------------------
