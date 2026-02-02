

TOPDIR = ../
INCLUDEDIR = $(TOPDIR)include
LIBDIR = $(TOPDIR)lib/
CXXFLAGS = -Wall -g -I $(INCLUDEDIR) -DQT

AVOID = 
INCLUDES = $(filter-out $(AVOID) ,$(wildcard $(INCLUDEDIR)/*.h))


all: testShowDisplay reticleExplorer testLineClipper testOperators testThreads testDynamicDisplay

testShowDisplay: objs/testShowDisplay.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o testShowDisplay objs/testShowDisplay.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

testLineClipper: objs/testLineClipper.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o testLineClipper objs/testLineClipper.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

testOperators: objs/testOperators.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o testOperators objs/testOperators.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

testThreads: objs/testThreads.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o testThreads objs/testThreads.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs`

reticleExplorer: objs/reticleExplorer.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o reticleExplorer objs/reticleExplorer.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs` -lboost_filesystem

testDynamicDisplay: objs/testDynamicDisplay.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o testDynamicDisplay objs/testDynamicDisplay.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs` -lboost_filesystem

objs/testShowDisplay.o: testShowDisplay.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testShowDisplay.o -c testShowDisplay.cpp `pkg-config opencv4 --cflags`

objs/testLineClipper.o: testLineClipper.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testLineClipper.o -c testLineClipper.cpp `pkg-config opencv4 --cflags`

objs/testOperators.o: testOperators.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testOperators.o -c testOperators.cpp `pkg-config opencv4 --cflags`

objs/testThreads.o: testThreads.cpp $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testThreads.o -c testThreads.cpp `pkg-config opencv4 --cflags`

objs/reticleExplorer.o:reticleExplorer.cpp  $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/reticleExplorer.o -c reticleExplorer.cpp `pkg-config opencv4 --cflags`

objs/testDynamicDisplay.o:testDynamicDisplay.cpp  $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/testDynamicDisplay.o -c testDynamicDisplay.cpp `pkg-config opencv4 --cflags`

clean: 
	rm objs/* testShowDisplay reticleExplorer testLineClipper testOperators testThreads testDynamicDisplay
