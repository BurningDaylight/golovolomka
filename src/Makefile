# Makefile for Golovolomka
# Copyright (C) 2009 Dmitry Potapov.

CC=g++

CFLAGS=-O -w
#CFLAGS=-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7
#CFLAGS=-g -DDEBUG
#CFLAGS=-O3 -Wall -Wwrite-strings -Wpointer-arith -Wconversion \
#           -Wstrict-prototypes -Wmissing-prototypes

CPP=$(CC) -E

LDFLAGS=

EXE=.exe

OBJS =  main.cpp figure.cpp figure_packer.cpp figure_packer_observer.cpp figure_rotator.cpp \
        figure_serialization.cpp figure_set_enumerator.cpp figure_transformation_enumerator.cpp \
        obj_writer.cpp transformed_figure.cpp typedef.cpp

all: main$(EXE)

main$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o *~ main$(EXE)

