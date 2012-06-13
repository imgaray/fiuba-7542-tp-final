CC = g++
CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -g -O0

INCLUDES = ../comun

I-INCLUDES = $(addprefix -I, $(INCLUDES))

EXTERNOBJS += $(addsuffix .o, $(basename ../comun/ArchivoConfiguracion.cpp))

all: PruebaArchivoConfiguracion

subdirs:
	for dir in $(INCLUDES); do \
		$(MAKE) -C $$dir; \
	done

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(EXTERNOBJS) $(I-INCLUDES) -c $<

PruebaArchivoConfiguracion: subdirs PruebaArchivoConfiguracion.cpp Pruebas.o
	$(CC) $(CXXFLAGS) $(EXTERNOBJS) $(I-INCLUDES) PruebaArchivoConfiguracion.cpp -o pruebaArchivoConfiguracion
