# Makefile

MAKE = make

CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors -O3 -g -pthread -lpthread

SUBDIRS = MotorDeConsultas servidor

CC = g++

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

all: main

subdirs:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	
main: subdirs
	$(CC) $(CXXFLAGS) -I$(SUBDIRS) main.cpp -o main

test: make_subs
	$(CC) $(CXXFLAGS) test.cpp -o test

clean: $(SUBDIRS)
	

.PHONY: all
