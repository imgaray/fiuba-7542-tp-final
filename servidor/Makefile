# Makefile

MAKE = make --no-print-directory

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = servidor ../comun MotorDeConsultas

EXTERNOBJS = $(addsuffix .o, $(basename  $(wildcard */*.cpp)))

EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../comun/*.cpp)))

DOCDIRS = servidor MotorDeConsultas

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
	
main: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp -o main

test: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean: $(SUBDIRS)
	$(LIMPIAR); for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	
.PHONY: all
