CXX_FLAG = --std=c++11 -g

all: tests game

tests: cards.h cards.cpp tests.cpp
	g++ -g ${CXX_FLAG} cards.h cards.cpp tests.cpp -o tests

game: cards.h cards.cpp main.cpp
	g++ -g ${CXX_FLAG} cards.h cards.cpp main.cpp -o game

testclass: tests
	./tests

clean:
	rm -f tests game *.o
