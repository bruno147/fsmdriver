FSMDriver
=========

A driver implementation using a Finite State Machine implementation to control its actions.


Finite State Machine
--------------------

A finite state machine can be described as device (or model of a device) that has a finite number of states it can be in at any given time, though it can only be in one state at any moment, and can operate on input to either make transitions from one state to another or to cause an output or action to take place.

States
------

The implemented states are:

### ApproachingCurve ###

Insert description.

### Curve ###

Insert description.

### InsideTrack ###

Insert description.

### OutOfTrack ###

Insert description.

### StraightLine ###

Insert description.

### Stuck ###

Insert description.

Transitions
-----------

Transitions between states are defined according to the sensor readings and the FSM's model.


FSMDriver5
----------

This implements a FSM with 5 states: ApproachingCurve, Curve, OutOfTrack, StraightLine, and Stuck.

FSMDriver3
----------

This implements a FSM with 3 states: InsideTrack, OutOfTrack, and Stuck.