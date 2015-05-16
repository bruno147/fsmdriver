FSMDriver
=========

This is an implementation of a [SCR](http://arxiv.org/abs/1304.1672) client controller using a Finite State Machine. Code was tested on Ubuntu 14.04 with TORCS 1.3.6.

Dependencies
------------

* [TORCS](http://torcs.sourceforge.net/) 1.3.4 (or higher). Be sure to install it from the [Source Package](http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=3#linux-src-all), and not a binary distribution (better yet, use the instructions below for installing the SCR patch).
* [SCR patch](http://sourceforge.net/projects/cig/files/SCR%20Championship/Server%20Linux/) as described in "Simulated Car Racing Championship Competition Software Manual" ([v2 - April 2013](http://arxiv.org/pdf/1304.1672v2)),

Usage
-----

A Makefile is provided in hopes of simplifying the build process. Assuming you've downloaded the code, FSMDriver can be compiled with:

```bash
cd path/to/fsmdriver
make
make DRIVER=FSMDriver5
```

This creates the default driver executable (```FSMDriver3```) and also ```FSMDriver5```. To test it (assuming you started a properly configured race), just run:

```bash
./bin/FSMDriver3
```

Documentation
-------------

Documentation (and further explanations) for the code is available in the source code files, and can be extracted via [Doxygen](www.doxygen.org). The Makefile provides the `info` target for this, and the output directory can be changed with in the `DOC_OUTPUT` variable. By default, the documentation is placed in the same directory as the Makefile.

```bash
make info DOC_OUTPUT=/doc/fsmdriver
```
