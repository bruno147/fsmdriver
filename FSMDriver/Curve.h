#ifndef FSMDRIVER_STATE_CURVE_H
#define FSMDRIVER_STATE_CURVE_H

#include "FSM.h"

class FSMDriver;

class Curve : public DrivingState<FSMDriver> {
public:
    static Curve *instance() {
        static Curve instance;
        return &instance;
    }

private:
    Curve() {}
    Curve(Curve const &);
    void operator=(Curve const&);

public:
    void enter(FSMDriver *driver) {
        std::cout << "Enter Curve" << std::endl;
    }

    void exit(FSMDriver *driver) {
        std::cout << "Exit Curve" << std::endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
	   	
int gear = 1;
float accel=1,accel0[4]= {0.8,0.7,0.85,1};
float steer = 0,steer0[20]={0,0.025,0.05,0.075,0.1,0.125,0.150,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.4,0.45,0.5,0.6,0.7,0.8};
float clutch=0;
float brake=0;
float brake0[3]={0,0.1,0.5};
float vx,vy;
float angle,angle_lim[5]={0.1,0.2,0.3,0.4,0.5};
float track_dis,track_lim[5]={0.1,0.2,0.3,0.4,0.5};
float factor[6] ={1,-10,-20,-30,-5,2.0};
float d_angle,d_track;
gear=cs.getGear();
vy = cs.getSpeedY();
vx = cs.getSpeedX();
angle = cs.getAngle();
track_dis = cs.getTrackPos();

d_angle = angle/abs(angle);
d_track = -track_dis/abs(track_dis);
d_track = d_angle*abs(angle)*35;

if(vx<1){
	vx =1;	
}

if((angle<angle_lim[0])&&(angle>-angle_lim[0])){
	if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
		steer = steer0[0]*d_track;
	}
	else{
		if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
			steer = steer0[3]*d_track;
		}
		else{
			if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
				steer = steer0[6]*d_track;
			}
			else{
				if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
					steer = steer0[9]*d_track;	
				}
				else{
					if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
						steer = steer0[11]*d_track;					
					}
					else{
						steer = steer0[15]*d_track;	
					}	
				}		
			}		
		}	
	}

}
else{
	if((angle<angle_lim[1])&&(angle>-angle_lim[1])){
		if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
			steer = steer0[3]*d_track;
		}
		else{
			if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
				steer = steer0[4]*d_track;
			}
			else{
				if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
					steer = steer0[7]*d_track;
				}
				else{
					if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
						steer = steer0[9]*d_track;
					}
					else{
						if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
							steer = steer0[12]*d_track;
						}
							
						else{
							steer = steer0[16]*d_track;	
						}	
					}		
				}		
			}	
		}
	}
	else{
		if((angle<angle_lim[2])&&(angle>-angle_lim[2])){
				if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
					steer = steer0[5]*d_track;
				}
				else{
					if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
						steer = steer0[6]*d_track;
					}
					else{
						if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
							steer = steer0[7]*d_track;
						}
						else{
							if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
								steer = steer0[10]*d_track;
							}
							else{
								if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
									steer = steer0[13]*d_track;
								}
								else{
									steer = steer0[17]*d_track;	
								}	
							}		
						}		
					}	
				}
		}
		else{
			if((angle<angle_lim[3])&&(angle>-angle_lim[3])){
				if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
					steer = steer0[6]*d_track;
				}
				else{
					if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
						steer = steer0[7]*d_track;
					}
					else{
						if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
							steer = steer0[9]*d_track;
						}
						else{
							if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
								steer = steer0[11]*d_track;
							}
							else{
								if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
									steer = steer0[14]*d_track;
								}
								else{
									steer = steer0[18]*d_track;	
								}	
							}		
						}		
					}	
				}
			}
			else{
				if((angle<angle_lim[4])&&(angle>-angle_lim[4])){
						if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
							steer = steer0[8]*d_track;
						}
						else{
							if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
								steer = steer0[9]*d_track;
							}
							else{
								if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
									steer = steer0[10]*d_track;
								}
								else{
									if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
										steer = steer0[12]*d_track;
									}
									else{
										if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
											steer = steer0[15]*d_track;
										}
										else{
											steer = steer0[19]*d_track;	
										}	
									}		
								}		
							}	
						}
				
				}
				else{
					if((track_dis<track_lim[0])&&(track_dis>-track_lim[0])){
						steer = steer0[9]*d_track;
					}
					else{
						if((track_dis<track_lim[1])&&(track_dis>-track_lim[1])){
							steer = steer0[10]*d_track;
						}
						else{
							if((track_dis<track_lim[2])&&(track_dis>-track_lim[2])){
								steer = steer0[11]*d_track;
							}
							else{
								if((track_dis<track_lim[3])&&(track_dis>-track_lim[3])){
									steer = steer0[12]*d_track;
								}
								else{
									if((track_dis<track_lim[4])&&(track_dis>-track_lim[4])){
										steer = steer0[14]*d_track;
									}	
									else{
										steer = steer0[20]*d_track;	
									}
								}		
							}		
						}	
					}
							
				}
							
			}
		}	
	}


}

if((steer>0.5)&&(gear>1)){
	gear=gear -1;
}

if(vx < 70){
	gear = 1;
}
else{
	if(vx < 100){
		gear = 2;
	}
	else{
		if(vx <150){
			gear = 3;
		}
		else{
			gear = 4;
		}
	}

}
printf("\n%f\n",steer);
clutch= factor[0]*vy;//According with the YSpeed


CarControl cc(accel,brake,gear,steer,clutch);

return cc;

	}

    ~Curve(){}
};

#endif // FSMDRIVER_STATE_CURVE_H
