newFSM Controller
====================


Description
-----------

A driver implementation using [Finite State Machine](FSM_Description.md)(FSM) to compete at Simulation Car Racing Championship at TORCS Simulator
environment, [Simulated Car Racing Championship](http://arxiv.org/abs/1304.1672). This file describes the basic configuration 
to compile and run the the FSMDriver controler, including libraries and commands to linux environment(Ubuntu).

Copyright
---------

This work use the src code developed by Daniele Loiacano.To understand the basic functions used at FSMDriver(such as drive, enter, shutdown) take a look at the folder src.


Requirement
-----------

A makefile is used to minimize the commands needed to compile and run the program.
Make sure to install the following programs and libraries:

* Torcs Simulator(at least 1.3.6). More information at: http://torcs.sourceforge.net/;

* Build-Essential: it contein dpkg, g++(at least 4.6 to provide support to c++11 standart), libc-dev and make;

* Cmake: it is important to build the program, reducing the effort to compile it;

* Doxygen(optional): a documentation programm to organize the comments and code properly; 

The packages can be installed following the command:
```
$ sudo apt-get install cmake build-essential
```
To install doxygen:
```
$ git clone https://github.com/doxygen/doxygen.git (optional)
$ cd doxygen
$ ./configure
$ make
$ make install
```

Usage
-----

The FSMDriver can drive at TORCS Simulator. It is build using makefile.


###Makefile 

Assuming that the previous requirements are fulfiled, the driver code can be build following the steps bellow:

```
$ cd ~/fsmdriver/build
$ cmake ..
$ make
```

The compiling process creates an executable named FSMDriver, to run it and torcs type the commands: 
```
$ cd ../bin
$ ./FSMDriver && torcs
```

At the Torcs' graphic interface, click: race -> Quick Race -> New Race.

Documentation
-------------

To better understand this code it is possible to use doxygen to generate an html file containing the this documentation.
Assuming that doxygen is installes follow the steps bellow:

```
$ cd ~/fsmdriver
$ doxygen -g D
$ doxygen D
$ doxygen doxyfile
$ firefox html/index.html
```





          
