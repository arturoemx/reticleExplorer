

INCLUDEDIR = ./include
LIBDIR = ./lib
CXXFLAGS = -Wall -g -I $(INCLUDEDIR) -DQT

INCLUDES = $(INCLUDEDIR)/showDisplay.h $(INCLUDEDIR)/geomFeatures.h $(INCLUDEDIR)/drawingFeatures.h $(INCLUDEDIR)/annotateImage.h  


all: testShowDisplay reticleExplorer testLineClipper testOperators

testShowDisplay: objs/testShowDisplay.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o testShowDisplay objs/testShowDisplay.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

testLineClipper: objs/testLineClipper.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o testLineClipper objs/testLineClipper.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

testOperators: objs/testOperators.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o testOperators objs/testOperators.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

reticleExplorer: objs/reticleExplorer.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o reticleExplorer objs/reticleExplorer.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs` -lboost_filesystem

objs/testShowDisplay.o: testShowDisplay.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testShowDisplay.o -c testShowDisplay.cpp `pkg-config opencv4 --cflags`

objs/testLineClipper.o: testLineClipper.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testLineClipper.o -c testLineClipper.cpp `pkg-config opencv4 --cflags`

objs/testOperators.o: testOperators.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testOperators.o -c testOperators.cpp `pkg-config opencv4 --cflags`

objs/reticleExplorer.o:reticleExplorer.cpp  $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/reticleExplorer.o -c reticleExplorer.cpp `pkg-config opencv4 --cflags`

clean: 
	rm objs/* testShowDisplay reticleExplorer testLineClipper testOperators
