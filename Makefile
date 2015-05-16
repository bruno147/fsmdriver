# @file Makefile
#
# @author Guilherme N. Ramos (gnramos@unb.br)
#
# Builds the controller specified by DRIVER argument.

#########
# Setup #
#########

# Default driver
DRIVER ?= FSMDriver3

# Compiler & flags
CC       = g++
CXXFLAGS = -Wall -std=c++11
EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER) -D __DRIVER_INCLUDE__='"$(DRIVER).h"'
# Uncomment the following line for a verbose client
# CXXFLAGS = -Wall -g -D __UDP_CLIENT_VERBOSE__

# Target [folder(s)]
BIN_DIR = bin
OBJ_DIR = obj
TARGET  = $(BIN_DIR)/$(DRIVER)

# Include directories
CLIENT_INC_DIR = include/client
DRIVER_INC_DIR = include/$(DRIVER)
FSM_INC_DIR    = include/FSM

# Source
CLIENT_SRC_DIR = src/client
CLIENT_SRC     = WrapperBaseDriver.cpp SimpleParser.cpp CarState.cpp CarControl.cpp
CLIENT_MAIN    = $(CLIENT_SRC_DIR)/client.cpp
DRIVER_SRC_DIR = src/$(DRIVER)
DRIVER_SRC     = $(DRIVER).cpp
FSM_SRC_DIR    = src/FSM
FSM_SRC        = $(notdir $(wildcard $(FSM_SRC_DIR)/*.cpp))

# Info
DOXYGEN    := $(shell doxygen --version 2>/dev/null)
DOXYFILE    = Doxyfile
DOC_OUTPUT ?= .

############
# Organize #
############
CLIENT_OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRC))
DRIVER_OBJ = $(OBJ_DIR)/$(DRIVER).o
FSM_OBJ    = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(FSM_SRC))

FLAGS      = $(CXXFLAGS) $(EXTFLAGS)
HEADERS    = $(addprefix -I,$(CLIENT_INC_DIR) $(FSM_INC_DIR) $(DRIVER_INC_DIR))
OBJECTS    = $(CLIENT_OBJ) $(FSM_OBJ) $(DRIVER_OBJ)

###########
# Targets #
###########
all: $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(CLIENT_SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) -I$(CLIENT_INC_DIR)

$(OBJ_DIR)/%.o: $(FSM_SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) -I$(FSM_INC_DIR) -I$(CLIENT_INC_DIR)

$(DRIVER_OBJ): $(DRIVER_SRC_DIR)/$(DRIVER_SRC) $(FSM_OBJ)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(HEADERS)

$(TARGET): dirs $(CLIENT_OBJ) $(DRIVER_OBJ) $(BIN_DIR)
	$(CC) $(FLAGS) -o $(TARGET) $(CLIENT_MAIN) $(HEADERS) $(OBJECTS)

info: $(DOXYFILE)
ifdef DOXYGEN
	( cat $(DOXYFILE) ; echo "OUTPUT_DIRECTORY=$(DOC_OUTPUT)" ) | doxygen -
else
	$(info "Doxygen not installed (http://www.doxygen.org).")
	exit 1
endif

clean:
	@rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* $(DOC_OUTPUT)/html
