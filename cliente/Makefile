# Makefile

MAKE = make

CXXFLAGS = -O0 -g -pthread -lpthread 

GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

# EN ESTA VARIABLE VAN TODOS LOS DIRECTORIOS QUE QUIERAN COMPILAR PARA
# USAR EN LA COMPILACION DEL MAIN
SUBDIRS = Vista Modelo ../comun

EXTERNOBJS =$(foreach path, $(SUBDIRS), $(addsuffix .o, $(basename  $(wildcard $(path)/*.cpp))))


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
	$(CC) $(CXXFLAGS) $(I-SUBDIRS) $(EXTERNOBJS) main.cpp $(GTKFLAGS) -o main

test: make_subs
	$(CC) $(CXXFLAGS) test.cpp -o test

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	

.PHONY: all
