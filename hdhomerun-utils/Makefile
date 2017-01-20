CXXFLAGS = -g -std=c++0x -Wall -Wextra -pedantic
CXX = g++
LIBHDHOMERUN = libhdhomerun/libhdhomerun.so

Tuner: Tuner.h Tuner.cpp 
	$(CXX) $(CXXFLAGS) -c Tuner.cpp 

test: Tuner.h Tuner.cpp test.cpp
	$(CXX) $(CXXFLAGS) -c Tuner.cpp 
	$(CXX) $(CXXFLAGS) test.cpp -o test Tuner.o $(LIBHDHOMERUN)
clean: 
	rm Tuner.o
	rm test
