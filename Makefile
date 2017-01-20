CXXFLAGS = -g -std=c++0x -Wall -Wextra -pedantic
CXX = g++
TUNER = hdhomerun-utils/Tuner.o
LIBHDHOMERUN = hdhomerun-utils/libhdhomerun/libhdhomerun.so
SERIALIB = serialibv1.2/serialib/serialib.o

measure: measure.cpp 
	$(CXX) $(CXXFLAGS) measure.cpp -o measure $(TUNER) $(LIBHDHOMERUN) $(SERIALIB)

clean: 
	rm measure
