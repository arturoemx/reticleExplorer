

INCLUDEDIR = ./include
LIBDIR = ./lib
CXXFLAGS = -Wall -g -I $(INCLUDEDIR) -DQT

INCLUDES = $(INCLUDEDIR)/reticleExplorer.h $(INCLUDEDIR)/showDisplay.h $(INCLUDEDIR)/geomFeatures.h $(INCLUDEDIR)/drawingFeatures.h $(INCLUDEDIR)/annotateImage.h  


all: testShowDisplay reticleExplorer

testShowDisplay: objs/testShowDisplay.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o testShowDisplay objs/testShowDisplay.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

reticleExplorer: objs/reticleExplorer.o lib/libAnnotate.a
	g++ $(CXXFLAGS) -o reticleExplorer objs/reticleExplorer.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs` -lboost_filesystem

objs/testShowDisplay.o: testShowDisplay.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testShowDisplay.o -c testShowDisplay.cpp `pkg-config opencv4 --cflags`

objs/reticleExplorer.o:reticleExplorer.cpp  $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/reticleExplorer.o -c reticleExplorer.cpp `pkg-config opencv4 --cflags`

clean: 
	rm objs/* testShowDisplay reticleExplorer
