/**  @file: FSMDriver3.h
 * @author: Guilherme N. Ramos (gnramos@unb.br)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. */

#ifndef UNB_FSMDRIVER_FSMDRIVER_3_H
#define UNB_FSMDRIVER_FSMDRIVER_3_H

#include "FSMDriver.h"

/** Defines a controller that uses a Finite State Machine with 3 states do model
 * its behavior. */
class FSMDriver3 : public FSMDriver {
public:
    /** Constructor. */
    FSMDriver3();

    /** Constructor.
     * @param argc *FSMDriver Constructor: instead of fixed parameters set by the code, this function receive it from the main, the FSMDriver can be used together with Genetic Algorithm using this function.*/
    // FSMDriver3(int argc, char** argv);

    /** Destructor */
    ~FSMDriver3();

    /* Inherited. */
    void onShutdown();

    /* Inherited. */
    void onRestart();

    /* Inherited */
    void init(float *);

    /* Inherited */
    void transition(CarState &cs);

    /* Inherited */
    CarControl wDrive(CarState cs);
};

#endif // UNB_FSMDRIVER_FSMDRIVER_3_H
