#include "ApproachingCurve.h"

ApproachingCurve::ApproachingCurve() {}

ApproachingCurve *ApproachingCurve::instance() {
    static ApproachingCurve instance;
    return &instance;
}

void ApproachingCurve::enter(FSMDriver *driver) {
    cout << "Enter ApproachingCurve" << endl;
    sensorsAreUpdated = false;
}

void ApproachingCurve::exit(FSMDriver *driver) {
    cout << "Exit ApproachingCurve" << endl;
}

CarControl ApproachingCurve::drive(FSMDriver *fsmdriver, CarState &cs) {
    if(!sensorsAreUpdated) /*@todo Só atualiza na 1a vez mesmo? */
        updateSensors(cs);

    const int focus = 0, meta = 0;
    const float clutch = 0;
	
	return CarControl(getAccel(cs), getBrake(cs), getGear(cs), cs.getAngle(), clutch, focus, meta);
	//Use the line below if the behavior of adjusting the car to the curve ahead is desired (not fully functional):
    //return CarControl(getAccel(cs), getBrake(cs), getGear(cs), getSteering(cs), clutch, focus, meta);
}

void ApproachingCurve::updateSensors(CarState &cs) {
    float speedFactor = 5000;                       //The target speed is obtained through a constant factor

    if (cs.getFocus(2) == -1) {                     //Focus sensors are available only once per second
        cout << "FOCUS MISS!" << endl;
        rSensor = cs.getTrack(10);                  //Use track sensors
        cSensor = cs.getTrack(9);
        lSensor = cs.getTrack(8);
    }
    else {
        cout << "FOCUS HIT!" << endl;
        rSensor = cs.getFocus(3);                   //Use focus sensors
        cSensor = cs.getFocus(2);
        lSensor = cs.getFocus(1);
    }
    targetSpeed = BASE_SPEED + speedFactor / fabs(lSensor - rSensor);

    sensorsAreUpdated = true;
}

float ApproachingCurve::getSteering(CarState &cs) {
    if(rSensor == lSensor) return 0;
    
    float angle = cs.getAngle();
    //If the controller is not in a pre-defined region amongst the inside limits of the track (between 0.7 and 0.9 with the current
    //set of values, normalized), than it will be adjusted to do so
    bool adjustedToCurve = ((fabs(cs.getTrackPos()) - TARGET_POS >= 0) && (fabs(cs.getTrackPos()) - TARGET_POS < 0.2));
    //Previous conditions:																// 0.2 is an arbitrary margin
    //bool adjustedToCurve = (cs.getTrackPos() <= TARGETPOS);

    if(!adjustedToCurve) {   
        if(approachingRightTurn())
            angle = MAX_STEERING - angle;
        else
            angle -= MAX_STEERING;
    }
    
    return angle;
}

float ApproachingCurve::getBrake(CarState &cs) {
    float brake = 0;
    float brakeFactor = 0.02;
    float diff = cs.getSpeedX() - targetSpeed;

    //if (fabs(cs.getSpeedX()) < 2) return 1;
    if (cs.getSpeedX() < 0) return 1;
    if (diff > 0) brake = brakeFactor * diff;

    return brake;
}


ApproachingCurve::~ApproachingCurve() {}
