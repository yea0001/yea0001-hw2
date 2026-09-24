#modify this makefile so that it will work for this new assignment
CC=g++

all: a.out
 
a.out: main.o
	$(CC) -std=c++11 main.o -o a.out
 
main.o: main.cpp
	$(CC) -c -std=c++11 main.cpp
 
clean:
	rm -f *.o *.out