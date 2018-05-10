# David Kelly 
# 10/10/2017
# Lab 4 Makefile
# Commands to  compile source code. 
# Usage: Type 'make' in project directory

EXE = barrier
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=Semaphore.h Barrier.h
CPPFILES=reusableBarrier.cpp Barrier.cpp Semaphore.cpp

# All .o files depend on .cpp file with same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(EXE) $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0 -Wall
DEBUG: ALL

# Remove the object files
CLEAN:
	rm *.o

