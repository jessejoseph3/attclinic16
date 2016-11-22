CXXFLAGS = -g -std=c++0x -Wall -Wextra -pedantic
CXX = g++
LIBHDHOMERUN = libhdhomerun/libhdhomerun.so

Tuner: Tuner.h Tuner.cpp 
	$(CXX) $(CXXFLAGS) Tuner.cpp -o Tuner $(LIBHDHOMERUN)

clean: 
	rm Tuner
