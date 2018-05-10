# David Kelly 
# 10/10/2017
# Lab 3 Makefile

EXE = mutex
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=Semaphore.h
CPPFILES=mutualexclusion.cpp Semaphore.cpp

# All .o files depend on .cpp file with same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CFILES)
	$(CC) -o $(EXE) $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

# Remove the object files
CLEAN:
	rm *.o

