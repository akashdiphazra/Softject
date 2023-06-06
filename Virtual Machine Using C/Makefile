CFLAGS= -Wall -Wextra -Wswitch-enum -std=c11 -pedantic -ggdb
LIBS=  

# .PHONY: all
all: ebasm vmi output     

ebasm: ebasm.c vm.c  
	$(CC) $(CFLAGS) -o virtualmachine ebasm.c $(LIBS)

vmi: vmi.c vm.c  
	$(CC) $(CFLAGS) -o vmi vmi.c $(LIBS)

output:
	./virtualmachine fib.ebasm fib.vm && ./vmi fib.vm
	# ./virtualmachine 123.ebasm 123.vm && ./vmi 123.vm

# .PHONY: examples
# examples: ./examples/fib.vm ./examples/123.vm

# ./examples/fib.vm: virtualmachine ./examples/fib.ebasm
# 	./virtualmachine ./examples/fib.ebasm ./examples/fib.vm

# ./examples/123.vm: virtualmachine ./examples/123.ebasm
# 	./virtualmachine ./examples/123.ebasm ./examples/123.vm

