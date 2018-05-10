# David Kelly 
# 10/10/2017
# Lab 5 Makefile
# Commands to  compile source code. 
# Usage: Type 'make' in project directory

EXE = program
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=Semaphore.h SafeBuffer.h
CPPFILES=prodCon.cpp SafeBuffer.cpp Semaphore.cpp

# All .o files depend on .cpp file with same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(EXE) $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0 -Wall
DEBUG: ALL

# Generate documentation
docs: 
	doxygen doxyfile

# Remove the object files
CLEAN:
	rm *.o

