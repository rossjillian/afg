CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

.PHONY:
default: amazons

amazons: amazons.o board.o 

amazons.o: amazons.hpp

board.o: board.hpp 

model-check: board.o

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM amazons model-check

.PHONY:
all: clean default
