CFLAGS= -Wall -Wextra -Wswitch-enum -std=c11 -pedantic -ggdb
LIBS=  

.PHONY: all

all: ebasm vmi run  

ebasm: ebasm.c vm.c  
	$(CC) $(CFLAGS) -o virtualmachine ebasm.c $(LIBS)

vmi: vmi.c vm.c  
	$(CC) $(CFLAGS) -o vmi vmi.c $(LIBS)

run:
	./virtualmachine fib.ebasm fib.vm && ./vmi fib.vm


