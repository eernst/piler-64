CFLAGS = -O3 -DNDEBUG=1
LDLIBS = -lm -static
# LDLIBS = -lm

OBJ = .o
EXE =

RM = rm -f
CP = cp

GPP = g++
LD = $(GPP) $(CFLAGS)
CPP = $(GPP) -c $(CFLAGS) 
CC = gcc -c $(CFLAGS) 

all: piler2

CPPSRC = $(sort $(wildcard *.cpp))
CPPOBJ	= $(subst .cpp,.o,$(CPPSRC))

$(CPPOBJ): %.o: %.cpp
	$(CPP) $< -o $@

piler2: $(CPPOBJ)
	$(LD) -o piler2 $(CPPOBJ) $(LDLIBS)
