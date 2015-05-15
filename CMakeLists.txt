cmake_minimum_required(VERSION 2.8)

project(FSMDriver)

include_directories(
    include
    states
    FSM
    FSMDriver3
    )

include_directories(states)
add_library(states SHARED
    states/Constants.cpp
    states/InsideTrack.cpp
    states/OutOfTrack.cpp
    states/Stuck.cpp
    states/StraightLine.cpp
    states/Curve.cpp
    states/ApproachingCurve.cpp
    )

add_library(base_driver SHARED
    src/CarControl.cpp
    src/CarState.cpp
    src/SimpleParser.cpp
    src/WrapperBaseDriver.cpp
    )


set(DRIVER FSMDriver)

# FSMDriver3

#Compiler flags
set(EXTFLAGS3 "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/FSMDriver3/FSMDriver3.h\"'")
add_definitions(-g -O3 -w -std=c++0x ${EXTFLAGS3})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(FSMDriver3 src/client.cpp FSMDriver3/FSMDriver3.cpp)
target_link_libraries(FSMDriver3 states base_driver)

# FSMDriver5

#Compiler flags
set(EXTFLAGS5 "-D __DRIVER_CLASS__=${DRIVER} -D __DRIVER_INCLUDE__='\"${CMAKE_SOURCE_DIR}/FSMDriver5/FSMDriver5.h\"'")
add_definitions(-g -O3 -w -std=c++0x ${EXTFLAGS5})

# Executable
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(FSMDriver5 src/client.cpp FSMDriver5/FSMDriver5.cpp)
target_link_libraries(FSMDriver5 states base_driver)
