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

OBJS =  \
  ./src/coord.cpp \
  ./src/figure.cpp \
  ./src/figure_packer.cpp \
  ./src/figure_packer_observer.cpp \
  ./src/figure_placement_heuristics.cpp \
  ./src/figure_rotator.cpp \
  ./src/figure_serialization.cpp \
  ./src/figure_set_enumerator.cpp \
  ./src/figure_transformation_enumerator.cpp \
  ./src/main.cpp \
  ./src/obj_writer.cpp \
  ./src/transformed_figure.cpp \
  ./src/typedef.cpp

all: ./bin/golovolomka

./bin/golovolomka: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o ./bin/golovolomka

clean:
	rm -f *.o *~ -o ./bin/golovolomka

