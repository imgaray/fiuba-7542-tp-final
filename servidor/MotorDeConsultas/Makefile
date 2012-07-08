# Makefile

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread

CC = g++

archivos = $(filter-out main.cpp test.cpp, $(wildcard *.cpp))

INCLUDES = ../../comun ../MotorDeConsultas

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

COMP_DEPEND = @echo "Compilar dependencias externos..."
LIMPIAR = @echo "Limpiando..."

#########################################


all: binaries

binaries: $(bin)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -I$(INCLUDES) -c $<

test: $(bin)
	$(CC) $(CXXFLAGS) $(bin) test.cpp -o test
	
clean:
	$(LIMPIAR); rm -f $(robjs)

.PHONY: clean all binaries doc
