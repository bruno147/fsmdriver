cmake_minimum_required(VERSION 2.8)

project(FSMDriver)


#Source files:
#include_directories(include FSMDriver3)
#set(SOURCES 
#	include/FSM/FSM.h
#	include/FSMDriver3/FSMDriver3.h
#	src/FSMDriver3/FSMDriver3.cpp
#	src/FSM/InsideTrack.cpp
#	src/FSM/OutOfTrack.cpp
#	src/FSM/Stuck.cpp
#	src/client/CarControl.cpp
#	src/client/CarState.cpp
#	src/client/client.cpp
#	src/client/SimpleParser.cpp
#	src/client/WrapperBaseDriver.cpp)
#
#Compiler flags
#set(DRIVER FSMDriver3)
#set(EXTFLAGS "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/include/${DRIVER}/${DRIVER}.h\"'")
#add_definitions(-g -O3 -Wall -std=c++0x ${EXTFLAGS})
# Executable
#set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#add_executable(${DRIVER} ${SOURCES})


include_directories(
    include
    )

include_directories(states)
add_library(states SHARED
    src/FSM/Constants.cpp
    src/FSM/InsideTrack.cpp
    src/FSM/OutOfTrack.cpp
    src/FSM/Stuck.cpp
    src/FSM/StraightLine.cpp
    src/FSM/Curve.cpp
    src/FSM/ApproachingCurve.cpp
    )

add_library(base_driver SHARED
    src/client/CarControl.cpp
    src/client/CarState.cpp
    src/client/SimpleParser.cpp
    src/client/WrapperBaseDriver.cpp
    )


set(DRIVER FSMDriver)

# FSMDriver3

#Compiler flags
set(EXTFLAGS3 "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/include/FSMDriver3/FSMDriver3.h\"'")
add_definitions(-g -O3 -w -std=c++0x ${EXTFLAGS3})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(FSMDriver3 src/client/client.cpp src/FSMDriver3/FSMDriver3.cpp)
target_link_libraries(FSMDriver3 states base_driver)

# FSMDriver5

#Compiler flags
set(EXTFLAGS5 "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/include/FSMDriver5/FSMDriver5.h\"'")
add_definitions(-g -O3 -w -std=c++0x ${EXTFLAGS5})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(FSMDriver5 src/client/client.cpp src/FSMDriver5/FSMDriver5.cpp)
target_link_libraries(FSMDriver5 states base_driver)
