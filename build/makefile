# Linux
CC=g++
LIBS= -lglut -lGLEW -lGL -lSOIL -lassimp

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Output directory
OUT_DIR= ../bin/

# Executable file
EXE = Gluttony

# Compiler flags
CXXFLAGS= -g -Wall -std=c++0x

# Source directory
SRC_DIR=../src

# Find all source files
SRC= $(shell find $(SRC_DIR) -name *.cpp)

# Convert all source files to object files
OBJ = $(SRC:%.cpp=%.o)

# Extra include paths
INCLUDE_PATHS=#-I/usr/include/freetype2

all: $(EXE)

$(EXE): $(OBJ)
	mkdir -p $(OUT_DIR) \
	&& $(CC) $(OBJ) -o $(OUT_DIR)$(EXE) $(LIBS) \
	&& make clean

%.o: %.cpp
	g++ -c $(CXXFLAGS) $(INCLUDE_PATHS)  $< -o $@

clean:
	-rm $(SRC_DIR)/*.o
	-rm $(SRC_DIR)/core/*.o
	-rm $(SRC_DIR)/program_states/*.o
