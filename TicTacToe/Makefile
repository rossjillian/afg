CC = g++ -std=c++2a
CXX = g++ -std=c++2a

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
