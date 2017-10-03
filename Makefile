Exe = sigexe
Cc = g++
Flags = -std=c++11 -pthread
Cfiles = signal.cpp Semaphore.cpp
Hfiles = Semaphore.h

all: $(Cfiles) $(Hfiles)
	$(Cc) $(Flags) *.cpp -o $(Exe)
