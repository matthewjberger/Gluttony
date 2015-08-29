# Linux
CC=g++
LIBS= -lglut -lGLEW -lGL

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Compiler flags
CXXFLAGS= -g -Wall -std=c++0x

# Source Files
OBJS= ../src/*.cpp

all: ../bin/Matrix

../bin/Matrix: ../src/main.cpp
	$(CC) $(CXXFLAGS) $(OBJS) -o ../bin/Matrix $(LIBS)

