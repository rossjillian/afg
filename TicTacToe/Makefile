CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

.PHONY:
default: tictactoe model-check model-check-timed

tictactoe: tictactoe.o board.o 

model-check: model-check.o board.o

model-check.o: tictactoe.hpp

model-check-timed: model-check-timed.o board.o

model-check-timed.o: tictactoe.hpp

tictactoe.o: tictactoe.hpp

board.o: board.hpp 

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM tictactoe model-check model-check-timed

.PHONY:
all: clean default
