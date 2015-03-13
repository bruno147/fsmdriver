cmake_minimum_required(VERSION 2.8)

project(FSMDriver)
find_package(Boost REQUIRED COMPONENTS filesystem system)

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

	# set(ROULLETE ON)
	set(ELITISM ON)
	# GA source
	set(GA_SOURCES
		FSMDriver\ Genetic\ Algorithm/DriverGeneticAlgorithm.h
		FSMDriver\ Genetic\ Algorithm/DriverGeneticAlgorithm.cpp)

	if(ROULLETE)
  		set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11 -D ROULLETE")
	endif()

	if(ELITISM)
  		set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11 -D ELITISM")
	endif()

	add_executable(DriverGeneticAlgorithm ${GA_SOURCES})
	target_link_libraries(DriverGeneticAlgorithm ${Boost_LIBRARIES})
endif()
