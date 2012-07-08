# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = ../comun 
#../servidor/MotorDeConsultas

EXTERNOBJS = $(foreach dir, $(SUBDIRS), $(addsuffix .o, $(basename  $(wildcard $(dir)/*.cpp))))

CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRS))

#bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

#######################################
#verbose = si

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  Compilando  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif

COMP_DEPEND = @echo "Compilar dependencias externas..."
LIMPIAR = @echo "Limpiando..."

#########################################


all: main

subdirs:
	$(COMP_DEPEND); for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
Agente.o: Agente.h Agente.cpp
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) -c Agente.cpp
	
main: subdirs Agente.o
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) Agente.h Agente.cpp main.cpp -o main

test: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean: $(SUBDIRS)
	$(LIMPIAR); for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(LIMPIAR); rm -f *.o

.PHONY: all
