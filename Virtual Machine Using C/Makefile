CFLAGS= -Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=  

all: compile run

compile:  
	$(CC) $(CFLAGS) -o virtualmachine vm.c $(LIBS)

run:
	./virtualmachine
