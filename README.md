FSMDriver Controller
====================


Description
-----------

A driver implementation using Finite State Machine(FSM) to compete at Simulation Car Racing Championship at TORCS Simulator
environment[Simulated Car Racing Championship](http://arxiv.org/abs/1304.1672). This file describes the basic configuration 
to compile and run the the FSMDriver controler, including libraries and commands to linux environment(Ubuntu).

### Finite State Machine

It is a concept where a machine is build by states that take the machine's control depending the state it is.
The FSMDriver has 5 states(Stra) and a function(transition), responsible to move the driver to each one depending the track configuration,
for example let say the sensor indicate that the car is inside the track in a straight line, an state named straightline take the control 
of the car. This approach results depends how well the machine's state describe the problem itself. 


Copyright
---------

This work use the src code developed by Daniele Loiacano.


Requirement
-----------

A makefile is used to minimize the commands needed to compile and run the program.
Make sure to install the following programs and libraries:

Torcs Simulator(at least 1.3.6). More information at: http://torcs.sourceforge.net/;

Build-Essential: it contein dpkg, g++(at least 4.6 to provide support to c++11 standart), libc-dev and make;

cmake: it is important to build the program, reducing the effort to compile it;

The packages can be installed following the command:
```
$ sudo apt-get install cmake build-essential
```

Usage
-----

The FSMDriver can drive at TORCS Simulator. It is build using makefile.


###Makefile 

Assuming that the previous requirements are fulfiled, the driver code can be build following the steps bellow:

```
$ cd ~/FSMDriver/build
$ cmake ..
$ make
```

The compiling process creates an executable named FSMDriver, to run it and torcs type the commands: 
```
$ cd ../bin
$ ./FSMDriver && torcs
```

At the Torcs' graphic interface, click: race -> Quick Race -> New Race.





          
