#include "FSMDriver.h"

#include "StraightLine.h"
typedef StraightLine StateStraightLine;

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
    State* p;
    if(cs.getTrackPos() > -1 && cs.getTrackPos() < 1) {
        // Getting track information from the sensor at +5 degrees towards the car axis
        float rSensor = cs.getTrack(10);
        // Getting track information from the sensor parallel to the car axis
        float cSensor = cs.getTrack(9);
        // Getting track information from the sensor at -5 degrees towards the car axis
        float lSensor = cs.getTrack(8);
        // Characteristics of a 'straight' to the FSM:
        // 		- If the central sensor is beyond the distance of maximum speed or if it
        // 		the biggest of {central, right (+5 degrees), left (-5 degrees)} sensors
        if (cSensor > 70 || (cSensor >= rSensor && cSensor >= lSensor)) {
            p = new StateStraightLine;
            cout << "Straight" << endl;
            return p;
        }
        // Characteristics of a 'curve' to the FSM
        else {
            // p = new StateCurve;
            p = new StateCurve;
            cout << "Curve" << endl;
            return p;
        }
    }
    // Characteristics of 'outside of track' states
    else {
        // Returns
        cout << "OutOfTrack" << endl;
        p = new StateOutOfTrack;
        return p;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//StateCurve Class
CarControl StateCurve::execute(FsmDriver *fsmdriver) {
    CarState cs = fsmdriver->getCarState();
    int gear = 1;
    float steer = 0;
    int gear0[3]={-1,1,2};//This set of gear were defined by tests
    float steer0[5]={0.1,0.6,-0.4,-0.8,-1};//This set of steer were defined by tests
    float accel,accel0[3]={0,0.5,1};//This set of accel were defined by tests
    float angle,angle_lim[4]={3.1415/2-1,-3.1415/2+1,0.1,-0.1};// angle and angles limits in this code
    float track_dis,track_lim[2]={0.2,-0.2};
    float factor[2]={1.5,1.2};//proportionate fator to steer, track_dis and angle


    accel=accel0[2];
    steer=steer0[0];
    gear = gear0[1];

    track_dis=cs.getTrackPos();
    angle = cs.getAngle();

    //printf("%f %f\n",angle,track_dis);
        if(((angle<angle_lim[0])&&(angle>angle_lim[1]))){// In the case the car is in the right direction

            if(((angle<angle_lim[2])&&(angle>angle_lim[3]))){

                if(((track_dis>track_lim[0])||(track_dis<track_lim[1]))){ //change the steer when the car is in a turn
                    gear =gear0[1];
                    steer=factor[0]*steer0[2]*track_dis;
                    accel = accel0[2];

                }

                else{
                    if((steer>0.05)&&(steer<-0.05)){
                        steer = steer-0.0001*steer/abs(steer);// Try to minimaze the steer when the condition of the track normalize(retiline) in order to maximaxe the speed
                    }
                    accel= accel0[2];
                    if(gear<5){
                        gear=gear+1;
                    }

                }
            }

            else{

                steer=-factor[1]*steer0[2]*angle/abs(angle);// Adjust the steer according with the angle.
                gear = gear0[1];
                accel = accel0[1];


            }

        }

        else{ //In the case the car is NOT in the right direction
            accel = accel0[1];
            steer= -steer0[3]*angle/abs(angle);
            gear = gear0[1];
        }

    CarControl cc(accel,0,gear,steer,0);

    return cc;

}



//-----------------------------------------------------------------------------------------------------------------
//StateOutOfTrack Class
float StateOutOfTrack::getBrake(CarState & cs){
    if(abs(cs.getSpeedY())>3){              //if the vehicle begins to skidding bigger than 3m/s in axis Y the brake will return 0.1
        return 0.1;
    }else{
        return 0;
    }
}
float StateOutOfTrack::getAccel(CarState & cs){
    return(1-abs(cs.getSpeedY())*0.1);        //can be negative, need some fix
}

int StateOutOfTrack::getGear(CarState & cs){
    if(cs.getSpeedX()>90){                      //out of track the gear control based on velocity seems better than the one based on rpm
        return cs.getGear();                    //need reverse behavior 
    }else if(cs.getSpeedX()>70){
        return 3;
    }else if(cs.getSpeedX()>40){
        return 2;
    }else{
        return 1;
    }
}
float StateOutOfTrack::getSteer(CarState & cs){
    if(cs.getTrackPos()>0){                 //aim to go back to the track with a range of angles, between 40 and 28 with relation to the axis of track
        if(cs.getAngle()>0.7){              //0.7rad is about 40 degrees
            return 1;
        }else if(cs.getAngle()<0.5){        //0.5rad is about 28 degress, this values are just a guess
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
