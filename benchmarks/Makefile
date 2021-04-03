CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

default: model_abstraction model_inline

model_abstraction:

model_inline:

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM model_abstraction model_inline

.PHONY:
all: clean model_abstraction model_inline
