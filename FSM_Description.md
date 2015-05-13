Finite State Machine
====================

It is a concept where a machine is builded by states that take the machine's control depending the state it is.
The newFSM has 3 states(InsideTrack, OutOfTrack and Stuck) and a function(transition), responsible to move the driver
to each one depending the track configuration, for example let say the sensor indicate that the car is outside the 
track due to a collion or a drive mislead, a state named OutOfTrack take the control of the car. This approach results 
depends how well the machine's state describe the problem itself.

The newFSM Finite State Machine was developed considering a set of possibilities that the driver can be applied. 
Firstly the car is inside or outside the track, the last one should be avoided once the speed of the car is reduce 
substantially outside the track.

The states alone do not make a FSM, the way to move from a state to another is accomplish here using a function called
transiction that perform the control's changes at state to state. 

Even though is possible to add more states it is important to say that would enhance the complexity to define a set of 
condition to each one.
