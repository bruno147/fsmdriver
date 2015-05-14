
Finite State Machine
====================

It is a concept where a machine is builded by states that take the machine's control depending the state it is.
>>>>>>> HEAD
The FSMDriver has 5 states(StraightLine, ApproachingCurve, Curve, OutOfTrack and Stuck) and a function(transition), 
responsible to move the driver to each one depending the track configuration, for example let say the sensor indicate 
that the car is inside the track in a straight line, an state named straightline take the control of the car. 
This approach results depends how well the machine's state describe the problem itself.

The FSMDriver Finite State Machine was developed considering a set of possibilities that the driver can be applied. 
Firstly the car is inside or outside the track. Inside there are the states StraightLine, ApproachingCurve and Curve, 
outside there are OutOfTrack and Stuck, both should be avoided once the speed of the car is reduce substantially outside 
the track. Lastly the track curvature define each state inside the track: the Straightline with low curvature, Curve
with high curvature and Approaching Curve a section of the track that is near a curve one.
The newFSM has 3 states(InsideTrack, OutOfTrack and Stuck) and a function(transition), responsible to move the driver
to each one depending the track configuration, for example let say the sensor indicate that the car is outside the 
track due to a collion or a drive mislead, a state named OutOfTrack take the control of the car. This approach results 
depends how well the machine's state describe the problem itself.

The newFSM Finite State Machine was developed considering a set of possibilities that the driver can be applied. 
Firstly the car is inside or outside the track, the last one should be avoided once the speed of the car is reduce 
substantially outside the track.
>>>>>>> newFsm

The states alone do not make a FSM, the way to move from a state to another is accomplish here using a function called
transiction that perform the control's changes at state to state. 

Even though is possible to add more states it is important to say that would enhance the complexity to define a set of 
condition to each one.
