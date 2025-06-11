
CXXFLAGS = -Wall -g -I ./ 

all: testShowDisplay

testShowDisplay: objs/testShowDisplay.o
	g++ $(CXXFLAGS) -o testShowDisplay objs/testShowDisplay.o `pkg-config opencv4 --libs`

objs/testShowDisplay.o: testShowDisplay.cpp showDisplay.h
	g++ $(CXXFLAGS) -o objs/testShowDisplay.o -c testShowDisplay.cpp `pkg-config opencv4 --cflags`


clean: 
	rm objs/* testShowDisplay 
