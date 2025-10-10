RANLIB=/usr/bin/ranlib

OPENCV_LIBS=`pkg-config --libs opencv4`

TOPDIR = ../
INCLUDEDIR = -I $(TOPDIR)include `pkg-config --cflags opencv4`
OBJDIR = ./objs/
.SUFFIXES: .cpp

CXXFLAGS += -g -Wall -D__VERBOSE__
LIB = libAnnotate.a

AVOID =


SRCS = $(filter-out $(AVOID) ,$(wildcard *.cpp))
OBJS = $(patsubst %.cpp,$(OBJDIR)%.o,$(SRCS))

all: install

install: build
	@echo Installing libraries
	mv $(LIB) $(TOPDIR)lib

build:$(OBJS)
	@echo Building libraries
	$(AR) r $(LIB) $(OBJDIR)*.o
	$(RANLIB) $(LIB)

$(OBJS): $(OBJDIR)%.o :%.cpp
	@echo COMPILING $<
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDEDIR)  $<

clean:
	rm $(OBJDIR)*.o $(TOPDIR)lib/$(LIB)
