# Makefile

MAKE = make --no-print-directory

CXXFLAGS = -g -O0 -pthread -lpthread

GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = Vista Modelo  ../comun ../servidor/MotorDeConsultas

SUBDIRSINCLUDE = Vista Modelo ../comun ../servidor/MotorDeConsultas Excepcion

EXTERNOBJS =$(foreach path, $(SUBDIRS), $(addsuffix .o, $(basename  $(wildcard $(path)/*.cpp))))


CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRSINCLUDE))

bin = $(archivos:.cpp=.o)

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
	$(COMP_DEPEND);for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

main: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp $(GTKFLAGS) -o main

test: make_subs
	$(CC) $(CXXFLAGS) test.cpp -o test

clean:
	$(LIMPIAR); for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done


.PHONY: all
