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