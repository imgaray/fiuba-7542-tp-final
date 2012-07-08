# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = ../comun ../servidor/MotorDeConsultas ../servidor/servidor

EXTERNOBJS = $(addsuffix .o, $(basename  $(wildcard */*.cpp)))

EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../comun/*.cpp)))

DOCDIRS = .
#../comun ../servidor/MotorDeConsultas ../servidor/servidor

archivos = $(filter-out main.cpp test.cpp, $(wildcard *.cpp))

bin = $(archivos:.cpp=.o)

CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRS))

#bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all:  main

binaries: $(bin)

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
pruebas: PruebaCSS.h PruebaCSS.cpp Pruebas.h Pruebas.C
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS)  -c Pruebas.h
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp -o pruebas
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp -o pruebas
	
main: subdirs pruebas
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(bin) $(EXTERNOBJS) main.cpp -o pruebas

#test: subdirs
#	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	
.PHONY: all
