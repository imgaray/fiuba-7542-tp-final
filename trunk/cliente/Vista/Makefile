# Makefile

CXXFLAGS = -O0 -g -pthread -lpthread

GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

CC = g++

archivos = $(filter-out main.cpp test.cpp, $(wildcard *.cpp))

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = ../../comun ../Modelo ../Excepcion

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all: binaries

binaries: $(bin)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $< $(GTKFLAGS)

test: $(bin)
	$(CC) $(CXXFLAGS) $(bin) test.cpp  -o test

clean:
	rm -f $(robjs)

.PHONY: clean all binaries
