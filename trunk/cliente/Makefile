# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O0 -g -pthread -lpthread `pkg-config gtkmm-2.4 --cflags` `pkg-config gtkmm-2.4 --libs`

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = Vista

EXTERNOBJS = $(addsuffix .o, $(basename  */*.cpp))

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
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp -o main

test: make_subs
	$(CC) $(CXXFLAGS) test.cpp -o test

clean: $(SUBDIRS)
	

.PHONY: all
