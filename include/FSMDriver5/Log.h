/**  @file: Log.h
 * @author: Bruno Macedo, Gabriel Araujo, Gabriel Sousa, Matheus Crestani, Yuri Galli, Guilherme N. Ramos (gnramos@unb.br)
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef UNB_FSMDRIVER_LOG_H
#define UNB_FSMDRIVER_LOG_H

#include "DrivingState.h"

#include <iostream>
#include <fstream>

/**Libraries used for shared memory between programms(Genetic Algorithm and the Driver)*/
#include <sys/shm.h>
#include <sys/stat.h>

class Log {
public:
    ~Log(){}
    /**Function to create a pointer to log(similar to a state)*/
    static Log *instance() {
        static Log instance;
        return &instance;
    }

    void updateLog(DrivingState *s, CarState cs) {
        assert(s);
        damage = cs.getDamage();

        if(dist_raced < cs.getDistFromStart()) dist_raced = cs.getDistFromStart();

        if(curveComplete(cs)){
            total_time += cs.getLastLapTime();
            total_dist_raced += dist_raced;
            dist_raced = 0;
            ofstream myfile;
            myfile.open("results.txt", std::ios_base::app);

            if(lapCounter==0){
                myfile << endl;
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

    //send total_time to shared memory
    void saveTotalTime(int segment_id){
        //if(lapCounter!=3) total_time=0;
        float* shared_memory;

        /* Attach the shared memory segment. */
        shared_memory = (float*) shmat (segment_id, 0, 0);

        cout << "total_time: " << total_time << endl;
        cout << "damage: " << damage << endl;
        cout << "total_dist_raced: " << total_dist_raced << endl;
        cout << "dist_raced: " << dist_raced << endl;

        /* Assigned shared memory */
        // shared_memory[0] = total_time;
        // shared_memory[1] = damage;
        // shared_memory[2] = dist_raced;
        shared_memory[0] = dist_raced;



        /* Detach the shared memory segment. */
        shmdt (shared_memory);
    }

    int curveComplete(CarState cs){
        if(cs.getDistFromStart()>20){
            flag = 1;
        }
        if(cs.getLastLapTime()==0){
            return 0;
        }else{
            if((cs.getDistFromStart()<5)&&(flag)){
                flag = 0;
                return 1;
            }else{
                return 0;
            }
        }
    }

private:
    Log(){}
    int lapCounter = 0;
    int flag = 0;
    float damage = 0;
    float dist_raced = 0;
    float total_time = 0;
    float total_dist_raced = 0;
};

#endif // UNB_FSMDRIVER_LOG_H
