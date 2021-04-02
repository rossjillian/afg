CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

tictactoe: tictactoe.o board.o

model-check: model-check.o board.o

model-check.o: tictactoe.hpp

tictactoe.o: tictactoe.hpp players.hpp

board.o: board.hpp

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM tictactoe model-check

.PHONY:
all: clean tictactoe model-check
