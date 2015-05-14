<<<<<<< HEAD
FSMDriver Controller
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

* Torcs Simulator(at least 1.3.4 or higher). More information at: http://torcs.sourceforge.net/;

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
$ ./FSMDriver & torcs
```

At the Torcs' graphic interface, click: race -> Quick Race -> New Race.

Documentation
-------------

To better understand this code it is possible to use doxygen to generate an html file containing the this documentation.
Please note that depending which driver you want to generate the documentation(via doxygen) it is needed to change the INPUT
files at Doxyfile to FSMDriver3 or FSMDriver5(by default it is set at FSMDriver3). Assuming that doxygen is installes follow
the steps bellow:

```
$ cd ~/fsmdriver
$ doxygen -g D
$ doxygen D
$ doxygen doxyfile
$ firefox html/index.html
```

        
=======
newFSM Controller
=================

This is an implementation of a [SCR](http://arxiv.org/abs/1304.1672) client controller using a Finite State Machine. Code was tested on Ubuntu 14.04 with TORCS 1.3.6.

Dependencies
------------

* [TORCS](http://torcs.sourceforge.net/) 1.3.4 (or higher). Be sure to install it from the [Source Package](http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=3#linux-src-all), and not a binary distribution (better yet, use the instructions below for installing the SCR patch).
* [SCR patch](http://sourceforge.net/projects/cig/files/SCR%20Championship/Server%20Linux/) as described in "Simulated Car Racing Championship Competition Software Manual" ([v2 - April 2013](http://arxiv.org/pdf/1304.1672v2)),

Usage
-----

A [CMakefile](http://www.cmake.org/documentation/) is provided in hopes of simplifying the build process (implying in additional ```make``` and ```cmake``` dependencies). Assuming you've downloaded the code, FSMDriver can be compiled with:

```bash
$ cd fsmdriver/build
$ cmake ..
$ make
```

This creates the executable ```FSMDriver```. To test it (assuming you started a properly configured race), just run:

```bash
./bin/FSMDriver
```

Documentation
-------------

Documentation (and further explanations) for the code is available in the source code files, and can be extracted via [Doxygen](www.doxygen.org).
>>>>>>> newFsm
