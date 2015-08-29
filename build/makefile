# Linux
CC=g++
LIBS= -lglut -lGLEW -lGL

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Executable file name and directory
EXE= ../bin/Gluttony

# Compiler flags
CXXFLAGS= -g -Wall -std=c++0x

# Source directory
SRC_DIR=../src

# Find all source files
SRC= $(shell find $(SRC_DIR) -name *.cpp)

# Convert all source files to object files
OBJ = $(SRC:%.cpp=%.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS) && make clean

%.o: %.cpp
	g++ -c $(CXXFLAGS) $< -o $@

clean:
	rm $(SRC_DIR)/*.o
	rm $(SRC_DIR)/core/*.o
	rm $(SRC_DIR)/program_states/*.o
