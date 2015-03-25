/** @file PID.h
  *
  * Describes a PID controller. 
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  */

#ifndef PID_H
#define PID_H

/** The proportional-integral-derivative driver uses a generic control loop 
 * feedback mechanism (controller) to keep a constant speed. A PID controller 
 * calculates an "error" value as the difference between a measured process 
 * variable and a desired setpoint. The controller attempts to minimize the error 
 * by adjusting the process control inputs. These values can be interpreted in 
 * terms of time: P depends on the present error, I on the accumulation of past 
 * errors, and D is a prediction of future errors, based on current rate of change.
 */
class PIDController {
  public:

	/** Constructor. */
	PIDController(float p /** Proportional gain. */ ,
				  float i /** Integral gain. */ ,
				  float d /** Derivative gain. */ ) : 
	Kp(p), Ki(i), Kd(d), previous_error(0), integral(0) {
	}

	/** Computes the output based on the previous iteration and the current situation. */
	float output(float setpoint /** Desired output. */ ,
				 float measured_value /** Current status. */ ,
				 float dt /** Elapsed time between iterations. */ ) {
		
		float current_error = setpoint - measured_value;
		integral += current_error * dt;

		float derivative = (current_error - previous_error) / dt;
		previous_error = current_error;

		return (Kp*current_error) + (Ki*integral) + (Kd*derivative);
	}

	void set(float p, float i, float d) {
	  Kp = p;
	  Ki = i;
	  Kd = d;
	}

  protected:
	float Kp /**< Proportional gain. */ ;
	float Ki /**< Integral gain. */ ;
	float Kd /**< Derivative gain. */ ;

  private:
	float previous_error /**< The error form the previous iteration. */ ;
	float integral /**< Integral value from the previous iteration. */ ;

};

#endif /* PID_H */
