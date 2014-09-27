cmake_minimum_required(VERSION 2.8)
project( FSMDriver )

# Compile Commands
# $ sudo apt-get install cmake
# $ cd ~/git/fSMdriver
# $ cmake .
# $ make
# $ ./bin/FSMDriver

# set(__DRIVER_CLASS__ FSMDriver)
# set(__DRIVER_INCLUDE__ "FSMDriver.h")
set(DRIVER "FSMDriver")
set(DRIVER_CLASS FsmDriver)
set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER_CLASS} -D __DRIVER_INCLUDE__='\"../${DRIVER}/${DRIVER}.h\"'")	
set(CMAKE_CXX_FLAGS "-Wall -O3 ${EXTFLAGS}")

include_directories(include)
set(FSMDRIVER_SRC
	FSMDriver/State.h
	FSMDriver/FSMDriver.h
	FSMDriver/FSMDriver.cpp
	# src/state.cpp
	src/CarControl.cpp
	src/CarState.cpp
	src/client.cpp
	src/SimpleParser.cpp
	src/WrapperBaseDriver.cpp
	# src/segmentadoras.cpp
	)

file(MAKE_DIRECTORY "bin")
add_executable(../bin/FSMDriver ${FSMDRIVER_SRC})
