CXXFLAGS = -g -std=c++0x -Wall -Wextra -pedantic
CXX = g++
LIBHDHOMERUN = libhdhomerun/libhdhomerun.so

Tuner: Tuner.h Tuner.cpp 
	$(CXX) $(CXXFLAGS) -c Tuner.cpp $(LIBHDHOMERUN)

clean: 
	rm Tuner
