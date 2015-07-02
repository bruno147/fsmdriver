/**  @file: Knowledge.cpp
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "Knowledge.h"

std::vector<Knowledge> memory = std::vector<Knowledge>();

Knowledge::Knowledge() {
    /* Nothing. */
}

Knowledge::Knowledge(float tSpeed, float lMark): targetSpeed(tSpeed), landmark(lMark) {
    /* Nothing. */
}
/**
 * @brief sort function for the class.
 * @details Auxiliar function that sort the objects of this class, auxiliates the sort function, std::algorithm.
 * 
 * @param l left operand
 * @param r right operand
 */
bool
Knowledge::aux_sort(const Knowledge& l, const Knowledge& r) {
    return (l.landmark < r.landmark);
}

Knowledge::~Knowledge() {
    /* Nothing. */
}
