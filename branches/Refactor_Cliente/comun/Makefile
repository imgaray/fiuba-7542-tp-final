# Makefile

CXXFLAGS = -Wall -O0 -g -pthread -lpthread

CC = g++

archivos = $(filter-out main.cpp test.cpp, $(wildcard *.cpp))

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES =  ../servidor/MotorDeConsultas ../servidor/servidor

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all: binaries

binaries: $(bin)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $<

test: $(bin)
	$(CC) $(CXXFLAGS) $(bin) test.cpp -o test
	
clean:
	rm $(robjs)

.PHONY: clean all binaries
