#ifndef CONSTANTS_H
#define CONSTANTS_H

extern int START_GEAR;
extern int LOW_GEAR_LIMIT;
extern int LOW_RPM;
extern int AVERAGE_RPM;
extern int HIGH_RPM;
extern int currentGear;
extern float BASE_SPEED;
extern float SPEED_FACTOR;

extern float STUCK_SPEED; // = 5;
extern unsigned int MIN_RACED_DISTANCE; // = 100;
extern unsigned int MAX_STUCK_TICKS; // = 300;
extern unsigned int MAX_SLOW_SPEED_TICKS; // =50;

extern float MAX_SKIDDING; // = 3;
extern float NEGATIVE_ACCEL_PERCENT; // = 0.1;
extern int VELOCITY_GEAR_4; // = 90;
extern int VELOCITY_GEAR_3; // = 70;
extern int VELOCITY_GEAR_2; // = 40;
extern float MAX_RETURN_ANGLE; // = 0.7;
extern float MIN_RETURN_ANGLE; // = 0.5;

#endif // CONSTANTS_H
