/**  @file: Knowledge.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <vector>
/**
 * @class Knowledge
 * @brief The Data Structure for Online Learning.
 * @details This class implements data structure for a Learning Algorithm, save the speed and the 'local' were the driver runs out of the track, such as a 'memory'. 
 */
class Knowledge {
public:
    float targetSpeed, landmark;
    
    Knowledge();
    Knowledge(float,float);

    static bool aux_sort(const Knowledge& l, const Knowledge& r);
    
    ~Knowledge();
};
// TODO retirar variavel global
extern std::vector<Knowledge> memory;


#endif // KNOWLEDGE_H
