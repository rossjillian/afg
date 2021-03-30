CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

tictactoe: board.o

tictactoe.o: tictactoe.hpp players.hpp

board.o: board.hpp

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM tictactoe

.PHONY:
all: clean tictactoe
