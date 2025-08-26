

INDR = ./include
CXXFLAGS = -Wall -g -I $(INDR)

INCLUDES = $(INDR)/reticleExplorer.h $(INDR)/showDisplay.h


all: testShowDisplay reticleExplorer

testShowDisplay: objs/testShowDisplay.o
	g++ $(CXXFLAGS) -o testShowDisplay objs/testShowDisplay.o `pkg-config opencv4 --libs`

reticleExplorer: objs/reticleExplorer.o
	g++ $(CXXFLAGS) -o reticleExplorer objs/reticleExplorer.o `pkg-config opencv4 --libs` -lboost_filesystem

objs/testShowDisplay.o: testShowDisplay.cpp $(INDR)/showDisplay.h
	g++ $(CXXFLAGS) -o objs/testShowDisplay.o -c testShowDisplay.cpp `pkg-config opencv4 --cflags`

objs/reticleExplorer.o:reticleExplorer.cpp $(INDR)/showDisplay.h
	g++ $(CXXFLAGS) -o objs/reticleExplorer.o -c reticleExplorer.cpp `pkg-config opencv4 --cflags`

clean: 
	rm objs/* testShowDisplay reticleExplorer
