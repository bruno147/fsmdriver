cmake_minimum_required(VERSION 2.8)

project(FSMDriver)

# Source files:
include_directories(include FSMDriver)
set(SOURCES 
	FSMDriver/FSM.h
	FSMDriver/FSMDriver.h
	FSMDriver/FSMDriver.cpp
	src/CarControl.cpp
	src/CarState.cpp
	src/client.cpp
	src/SimpleParser.cpp
	src/WrapperBaseDriver.cpp)

# Compiler flags
set(DRIVER FSMDriver)
set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/${DRIVER}/${DRIVER}.h\"'")	
add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(${DRIVER} ${SOURCES})

# GA Flag
 set(GA ON)

# GA
if(GA)
	include_directories(include FSMDriver Genetic Algorithm)

	# GA source
	set(GA_SOURCES
		FSMDriver\ Genetic\ Algorithm/DriverGeneticAlgorithm.h
		FSMDriver\ Genetic\ Algorithm/DriverGeneticAlgorithm.cpp)

	add_executable(DriverGeneticAlgorithm ${GA_SOURCES})
endif()
