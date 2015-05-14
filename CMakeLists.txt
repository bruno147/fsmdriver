cmake_minimum_required(VERSION 2.8)

project(FSMDriver)

# Source files:
include_directories(include FSMDriver)
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

# Compiler flags
set(DRIVERF FSMDriver3)
set(DRIVER FSMDriver)
set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/${DRIVERF}/${DRIVERF}.h\"'")
add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${DRIVERF} ${SOURCES})

