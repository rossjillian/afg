CC = g++ -std=c++20
CXX = g++ -std=c++20

INCLUDES = -I../include

CXXFLAGS = -g -Wall -O2 $(INCLUDES)

LDFLAGS = 
LDLIBS = 

tests: model_unittests
	./model_unittests

model_unittests:

.PHONY:
clean:
	rm -rf *.o a.out *.dSYM model_unittests

.PHONY:
all: clean test_model 
