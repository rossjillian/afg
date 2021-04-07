CC = g++ -std=c++20

CXX = g++ -std=c++20

INCLUDES = -I../include -I../TicTacToe 

CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

tests: model_unittests ai_unittests

ai_unittests: ../TicTacToe/board.o

../TicTacToe/board.o: ../TicTacToe/board.hpp

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM model_unittests ai_unittests

.PHONY:
all: clean tests
