# Makefile

MAKE = make --no-print-directory

CXXFLAGS =  -O0 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = ../comun ../servidor/MotorDeConsultas ../servidor/servidor ../agente

EXTERNOBJS = $(addsuffix .o, $(basename  $(wildcard */*.cpp)))

EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../comun/*.cpp)))
#EXTERNOBJS += $(addsuffix .o, $(basename  $(filter-out  main.cpp, $(wildcard ./*.cpp))))
EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../servidor/servidor/*.cpp)))
EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../servidor/MotorDeConsultas/*.cpp)))
EXTERNOBJS += $(addsuffix .o, $(basename  $(wildcard ../agente/A*.cpp)))

DOCDIRS = ../comun ../servidor/MotorDeConsultas ../servidor/servidor

archivos = $(filter-out  main.cpp, $(wildcard *.cpp))

EXTERNOBJS += $(addsuffix .o, $(basename $(archivos)))

bin = $(archivos:.cpp=.o)

CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRS))

#bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

misobj = $(wildcard *.o)

######################################################
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

######################################################

all:  pruebas

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) -c $<

binaries: $(bin)

subdirs:
	$(COMP_DEPEND); for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

pruebas: binaries subdirs 
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp -o pruebas


#test: subdirs
#	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) test.cpp -o test

clean: $(SUBDIRS)
	$(LIMPIAR); for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(LIMPIAR); rm -f *.o
	
.PHONY: all
