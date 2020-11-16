# Copyright (C) 2005, 2010 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

##########################################################################
#    You can modify this example makefile to fit for your own program.   #
#    Usually, you only need to change the four CHANGEME entries below.   #
##########################################################################

# CHANGEME: This should be the name of your executable
EXE = data_main

# CHANGEME: Here is the name of all object files corresponding to the source
#           code that you wrote in order to define the problem statement
OBJS = data_main.o \


# CHANGEME: Additional libraries
ADDLIBS =

# CHANGEME: Additional flags for compilation (e.g., include flags)
ADDINCFLAGS =

##########################################################################
#  Usually, you don't have to change anything below.  Note that if you   #
#  change certain compiler options, you might have to recompile Ipopt.   #
##########################################################################

# C++ Compiler command
CXX = /usr/local/bin/g++-10

# C++ Compiler options
CXXFLAGS = -O2 -DNDEBUG 

# additional C++ Compiler options for linking
CXXLINKFLAGS = 

prefix=/usr/local
exec_prefix=${prefix}

# Include directories
#INCL = `PKG_CONFIG_PATH=/usr/local/lib/pkgconfig: pkg-config --cflags ipopt` $(ADDINCFLAGS)
#INCL = -I${prefix}/include/coin-or -I/usr/local/include/coin-or/hsl    -DIPOPTLIB_BUILD $(ADDINCFLAGS)

# Linker flags
$LIBS = `PKG_CONFIG_PATH=/usr/local/lib/pkgconfig: pkg-config --libs ipopt`
#LIBS = -L${exec_prefix}/lib -lipopt -L/usr/local/lib -lcoinhsl  -framework Accelerate  -ldl

all: $(EXE)

.SUFFIXES: .cpp .o

$(EXE): $(OBJS)
	$(CXX) $(CXXLINKFLAGS) $(CXXFLAGS) -o $@ $(OBJS) $(ADDLIBS) $(LIBS)

clean:
	rm -rf $(EXE) $(OBJS) 

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<
