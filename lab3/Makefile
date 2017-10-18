# @author: David Kelly
# @date:   10/10/2017 

Exe = mutex
Cc = g++
Flags = -std=c++11 -pthread
Cfiles = mutualexclusion.cpp Semaphore.cpp
Hfiles = Semaphore.h
RM = rm

all: $(Cfiles) $(Hfiles)
	$(Cc) $(Flags) *.cpp -o $(Exe) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

clean: 
	$(RM) *.o *~
