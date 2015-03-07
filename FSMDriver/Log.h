#ifndef LOG_H
#define LOG_H

#include "FSM.h"

#include <iostream>
#include <fstream>

//For shared memory
#include <sys/shm.h>
#include <sys/stat.h>

class FSMDriver;

class Log {
public:
    ~Log(){}
    static Log *instance() {
        static Log instance;
        return &instance;
    }
    void updateLog(DrivingState<FSMDriver> *s, CarState cs) {
        assert(s);
        damage=cs.getDamage();
        distRaced=cs.getDistRaced();
        
        if(curveComplete(cs)){
            //lap++;
            totalTime+=cs.getLastLapTime();
            /*
            ofstream myfile;
            myfile.open("results.txt", std::ios_base::app);
            myfile << "Lap";
            myfile << lap;
            myfile << " ";
            myfile << cs.getLastLapTime();
            myfile << ";";
            myfile.close();
            */
            lapCounter++;
        }

    }

    void saveLog(){
        ofstream myfile;
        myfile.open("results.txt");
        myfile << "Damage " << damage;
        myfile << ";DistRaced " << distRaced;
        myfile << ";total_time " << totalTime;
        myfile << ";";
        myfile << endl;
        myfile.close();
    }

    /*
    void saveTotalTime(){
        ofstream myfile;
        myfile.open("results.txt");
        myfile << totalTime;
        myfile.close();
    }
    */


    //send totalTime to shared memory
    void saveTotalTime(int segment_id){
        if(lapCounter!=3) totalTime=0;


        char* shared_memory;

        /* Attach the shared memory segment. */
        shared_memory = (char*) shmat (segment_id, 0, 0);

        //Assigned shared memory
        sprintf (shared_memory, "%f", totalTime);


        /* Detach the shared memory segment. */
        shmdt (shared_memory);

    }
    int curveComplete(CarState cs){
        if(cs.getDistFromStart()>20){
            flag=1;
        }
        if(cs.getLastLapTime()==0){
            return 0;
        }else{
            if((cs.getDistFromStart()<5)&&(flag)){
                flag=0;
                return 1;
            }else{
                return 0;
            }
        }
    }
private:
    Log(){}
    int lap=0;
    int flag=0;
    int damage=0;
    int distRaced=0;
    float totalTime=0;
    int lapCounter=0;


};



#endif // LOG_H
