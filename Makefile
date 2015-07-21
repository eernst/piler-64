CFLAGS = -O3 -DNDEBUG=1
#LDLIBS = -lm -static
LDLIBS = -lm

OBJ = .o
EXE =

RM = rm -f
CP = cp

GPP = g++
LD = $(GPP) $(CFLAGS)
CPP = $(GPP) -c $(CFLAGS) 
CC = gcc -c $(CFLAGS)

binary = piler-64

all: $(binary)

CPPSRC = $(sort $(wildcard *.cpp))
CPPOBJ = $(subst .cpp,.o,$(CPPSRC))

$(CPPOBJ): %.o: %.cpp
	$(CPP) $< -o $@

piler-64: $(CPPOBJ)
	$(LD) -o $(binary) $(CPPOBJ) $(LDLIBS)

clean:
	$(RM) *.o $(binary)
