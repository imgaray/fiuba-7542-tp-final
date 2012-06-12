# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = ../comun

EXTERNOBJS = $(addsuffix .o, $(basename  $(wildcard */*.cpp)))

EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../comun/*.cpp)))

CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRS))

#bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all: main

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
main: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) Agente.h Agente.cpp main.cpp -o main

test: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	

.PHONY: all