/**  @file: DrivingState.cpp
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#include "DrivingState.h"
#include "FSMDriver.h"

DrivingState::DrivingState(FSMDriver *o) : owner(o) {
	assert(owner);
}

DrivingState::~DrivingState() {
	/* Nothing. */
}

void
DrivingState::enter() {
	/* Nothing. */
}

void
DrivingState::exit() {
	/* Nothing. */
}
