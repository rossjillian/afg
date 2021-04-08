CC = g++-10.1 -std=c++20
CXX = g++-10.1 -std=c++20

INCLUDES = -I../include -I../TicTacToe

CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

default: model_abstraction model_inline ai_abstraction

model_abstraction:

model_inline:

ai_abstraction: ../TicTacToe/players.hpp ../TicTacToe/tictactoe.hpp

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM model_abstraction model_inline ai_abstraction

.PHONY:
all: clean model_abstraction model_inline ai_abstraction
