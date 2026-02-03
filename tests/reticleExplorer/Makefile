

TOPDIR = ../../
INCLUDEDIR = $(TOPDIR)include
LIBDIR = $(TOPDIR)lib/
CXXFLAGS = -Wall -g -I $(INCLUDEDIR) -DQT

AVOID = 
INCLUDES = $(filter-out $(AVOID) ,$(wildcard $(INCLUDEDIR)/*.h))


all: reticleExplorer

reticleExplorer: objs/reticleExplorer.o $(LIBDIR)libAnnotate.a
	g++ $(CXXFLAGS) -o reticleExplorer objs/reticleExplorer.o -L$(LIBDIR) -lAnnotate `pkg-config opencv4 --libs` -lboost_filesystem

objs/reticleExplorer.o:reticleExplorer.cpp  $(INCLUDES)
	g++ $(CXXFLAGS) -o objs/reticleExplorer.o -c reticleExplorer.cpp `pkg-config opencv4 --cflags`

clean:
	rm objs/* reticleExplorer
