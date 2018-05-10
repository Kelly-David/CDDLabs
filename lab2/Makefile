# David Kelly 
# 03/10/2017
# Lab 1 Makefile

EXE = rendevous
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES=Semaphore.h
CPPFILES=rendevous.cpp Semaphore.cpp

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
