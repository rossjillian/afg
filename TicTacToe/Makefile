CC = g++-10.1 -std=c++20
CXX = g++-10.1 -std=c++20

INCLUDES = -I../include

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

.PHONY:
default: tictactoe model-check

tictactoe: tictactoe.o board.o 

model-check: model-check.o board.o

model-check.o: tictactoe.hpp

tictactoe.o: tictactoe.hpp strategy.hpp players.hpp

board.o: board.hpp 

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM tictactoe model-check

.PHONY:
all: clean default
