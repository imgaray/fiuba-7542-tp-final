# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O3 -g -pthread -lpthread

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = MotorDeConsultas servidor

CC = g++

I-SUBDIRS = $(addprefix -I, $(SUBDIRS))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all: main

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
main: subdirs
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) main.cpp -o main

test: make_subs
	$(CC) $(CXXFLAGS) test.cpp -o test

clean: $(SUBDIRS)
	

.PHONY: all
