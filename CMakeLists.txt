cmake_minimum_required(VERSION 2.8)

project(FSMDriver)

# Source files:
#include_directories(include FSMDriver5)
#set(SOURCES 
#	FSMDriver5/FSM.h
#	FSMDriver5/FSMDriver5.h
#	FSMDriver5/FSMDriver5.cpp
#	FSMDriver5/StraightLine.cpp
#	FSMDriver5/Curve.cpp
#	FSMDriver5/ApproachingCurve.cpp
#	FSMDriver5/OutOfTrack.cpp
#	FSMDriver5/Stuck.cpp
#	src/CarControl.cpp
#	src/CarState.cpp
#	src/client.cpp
#	src/SimpleParser.cpp
#	src/WrapperBaseDriver.cpp)
#
# Compiler flags
#set(DRIVER FSMDriver5)
#set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/${DRIVER}/${DRIVER}.h\"'")
#add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})

# Executable
#set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#add_executable(${DRIVER} ${SOURCES})


#Source files:
include_directories(include FSMDriver5)
set(SOURCES 
	FSMDriver3/FSM.h
	FSMDriver3/FSMDriver3.h
	FSMDriver3/FSMDriver3.cpp
	FSMDriver3/InsideTrack.cpp
	FSMDriver3/OutOfTrack.cpp
	FSMDriver3/Stuck.cpp
	src/CarControl.cpp
	src/CarState.cpp
	src/client.cpp
	src/SimpleParser.cpp
	src/WrapperBaseDriver.cpp)

#Compiler flags
set(DRIVER FSMDriver3)
set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/${DRIVER}/${DRIVER}.h\"'")
add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})
# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${DRIVER} ${SOURCES})

