cmake_minimum_required(VERSION 2.8)
project( FsmDriver )

# Compile Commands
# $ sudo apt-get install cmake
# $ cd ~/git/fsmdriver
# $ cmake .
# $ make
# $ ./bin/FsmDriver

# set(__DRIVER_CLASS__ FsmDriver)
# set(__DRIVER_INCLUDE__ "FsmDriver.h")
set(CMAKE_CXX_FLAGS "-Wall -O3")

include_directories(include)
set(FSMDRIVER_SRC
	src/FsmDriver.cpp
	# src/state.cpp
	src/CarControl.cpp
	src/CarState.cpp
	src/client.cpp
	src/SimpleParser.cpp
	src/WrapperBaseDriver.cpp
	# src/segmentadoras.cpp
	)

file(MAKE_DIRECTORY "bin")
add_executable(bin/FsmDriver ${FSMDRIVER_SRC})
