# @author: David Kelly
# @date:   10/10/2017 

Exe = barrier
Cc = g++
Flags = -std=c++11 -pthread
Cfiles = barrierExample.cpp Semaphore.cpp
Hfiles = Semaphore.h
RM = rm

all: $(Cfiles) $(Hfiles)
	$(Cc) $(Flags) *.cpp -o $(Exe) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

clean: 
	$(RM) *.o *~
