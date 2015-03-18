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

        if(distRaced<cs.getDistFromStart()) distRaced=cs.getDistFromStart();
        
        if(curveComplete(cs)){
            totalTime+=cs.getLastLapTime();
            totalDistRaced+=distRaced;
            distRaced=0;
            ofstream myfile;
            myfile.open("results.txt", std::ios_base::app);

            if(lapCounter==0){
                myfile<<endl;
            }

            myfile << "Lap";
            myfile << lapCounter;
            myfile << " ";
            myfile << cs.getLastLapTime();
            myfile << ";";
            myfile << " Damage " << damage << "; ";

            myfile.close();
            
            lapCounter++;
        }

    }

    /*void saveLog(){
        ofstream myfile;
        myfile.open("results.txt");
        myfile << "Damage " << damage;
        myfile << ";DistRaced " << distRaced;
        myfile << ";total_time " << totalTime;
        myfile << ";";
        myfile << endl;
        myfile.close();
    }*/

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
        //if(lapCounter!=3) totalTime=0;


        char* shared_memory;

        /* Attach the shared memory segment. */
        shared_memory = (char*) shmat (segment_id, 0, 0);


        cout << "totalTime: " << totalTime << endl;
        cout << "damage: " << damage << endl;
        cout << "totalDistRaced: " << totalDistRaced << endl;
        cout << "distRaced: " << distRaced << endl;
        
        //Assigned shared memory
        if(lapCounter==3){
            sprintf (shared_memory, "%f %f %f", totalTime, damage, totalDistRaced+distRaced);
        }else{
            sprintf (shared_memory, "%f %f %f", totalTime, damage, totalDistRaced);
        }



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
    int lapCounter=0;
    int flag=0;
    float damage=0;
    float distRaced=0;
    float totalTime=0;
    float totalDistRaced=0;


};



#endif // LOG_H
