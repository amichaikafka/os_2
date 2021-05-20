CC=gcc
AR=ar 
FLAGS=-Wall -g


all:  task1 task2

task1: solution.c 
	gcc -o solution solution.c -lpthread -lm
task2: primeSlow.c 
	gcc -o primeSlow primeSlow.c 

.PHONY: clean all	  


clean:
	-rm -f *.o *.so  prime
