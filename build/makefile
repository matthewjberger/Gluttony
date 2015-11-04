# Linux
CC = g++
LIBS = -lglut -lGLEW -lGL -lSOIL -lassimp -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Output directory
OUT_DIR = ../bin/

# Executable file
EXE = AirHockey

# Compiler flags
CXXFLAGS= -g -w -std=c++0x

# Source directory
SRC_DIR=../src

# Find all source files
SRC= $(shell find $(SRC_DIR) -name *.cpp)

# Convert all source files to object files
OBJ = $(SRC:%.cpp=%.o)

# Extra include paths
INCLUDE_PATHS=-I/usr/include/bullet

all: $(EXE)

$(EXE): $(OBJ)
	mkdir -p $(OUT_DIR) \
	&& $(CC) $(OBJ) $(INCLUDE_PATHS) -o $(OUT_DIR)$(EXE) $(LIBS) \

%.o: %.cpp
	g++ -c $(CXXFLAGS) $(INCLUDE_PATHS)  $< -o $@

clean:
	-rm $(SRC_DIR)/*.o
	-rm $(SRC_DIR)/core/*.o
	-rm $(SRC_DIR)/program_states/*.o
