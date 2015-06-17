/**  @file: FSMDriver.cpp
 * @author: Bruno Macedo, Gabriel Araujo, Gabriel Sousa, Matheus Crestani, Yuri Galli, Guilherme N. Ramos (gnramos@unb.br)
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */

#include "FSMDriver.h"

FSMDriver::FSMDriver() : current_state(nullptr), previous_state(nullptr) {
}

FSMDriver::~FSMDriver() {
	/* Nothing */
}

void
FSMDriver::changeTo(DrivingState *state) {
	assert(state);
	previous_state = current_state;
	current_state = state;
}

void
FSMDriver::revertState() {
	changeTo(previous_state);
}

CarControl
FSMDriver::wDrive(CarState cs) {
	transition(cs);
	return current_state->drive(cs);
}
