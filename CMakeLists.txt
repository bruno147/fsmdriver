cmake_minimum_required(VERSION 2.8)
project( fsmdriver )

set(CMAKE_CXX_FLAGS "-Wall -O3")

include_directories(${FSMDRIVER_SOURCE_DIR}/include)
set(FSMDRIVER_SRC
	${FSMDRIVER_SOURCE_DIR}/src/fsmdriver.cpp
	${FSMDRIVER_SOURCE_DIR}/src/state.cpp
	# ${FSMDRIVER_SOURCE_DIR}/src/segmentadoras.cpp
	)

file(MAKE_DIRECTORY "bin")
add_executable(bin/fsmdriver ${FSMDRIVER_SRC})
