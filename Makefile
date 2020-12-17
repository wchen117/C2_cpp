# Copyright (C) 2005, 2010 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

##########################################################################
#    You can modify this example makefile to fit for your own program.   #
#    Usually, you only need to change the four CHANGEME entries below.   #
##########################################################################

# CHANGEME: This should be the name of your executable
# CHANGEME: This should be the name of your executable
EXE = main_1

# CHANGEME: Here is the name of all object files corresponding to the source
#           code that you wrote in order to define the problem statement
OBJS = main_1.o \
	   data.o \
	   raw.o \
	   con.o \
	   sup.o \
	   caseidentification.o \
	   bus.o \
	   load.o \
	   fixedshunt.o \
	   generator.o \
	   transformer.o \
	   nontransformerbranch.o \
	   area.o \
	   transformerimpedancecorrectiontable.o \
	   zone.o \
	   owner.o \
	   switchedshunt.o \
	   contingency.o \
	   generatoroutevent.o \
	   branchoutevent.o \
	   sup_generator.o \
	   sup_line.o \
	   sup_load.o \
	   sup_transformer.o \
	   sup_cblock.o \
	   sup_pcblock.o \
	   sup_qcblock.o \
	   sup_scblock.o 

# CHANGEME: Additional libraries
ADDLIBS =

# CHANGEME: Additional flags for compilation (e.g., include flags)
ADDINCFLAGS =

# C++ Compiler command
CXX = /usr/bin/g++ -std=c++11
#CXX = /usr/local/bin/g++-10

# C++ Compiler options
CXXFLAGS = -O2 -DNDEBUG 

# additional C++ Compiler options for linking
CXXLINKFLAGS = 

prefix=/usr/local
exec_prefix=${prefix}

# Include directories

INCL = -I/Users/wchen/Softwares/JsonCpp/vcpkg/packages/rapidjson_x64-osx/include -I/Users/wchen/Softwares/boost_1_63_0/boost

# Linker flags
#LIBS = -framework Accelerate -ldl
#LIBS = -L${exec_prefix}/lib -lipopt -L/usr/local/lib -lcoinhsl  -framework Accelerate  -ldl

all: $(EXE)

.SUFFIXES: .cpp .o

$(EXE): $(OBJS)
	$(CXX) $(CXXLINKFLAGS) $(CXXFLAGS) -o $@ $(OBJS) $(ADDLIBS) $(LIBS)

clean:
	rm -rf $(EXE) $(OBJS) 

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<
