CC=g++ 
CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -pedantic -ggdb
EXEC = akash
OBJS = Shallow.o main.o # List of object files needed to
MEMORY_SAFE_FLAGS= -fsanitize=address -fno-omit-frame-pointer

all: compile clean run

#@ for supressing the compilation messages
compile: ${OBJS}
	@${CC} ${CXXFLAGS} -o ${EXEC} ${OBJS} ${MEMORY_SAFE_FLAGS}

Shallow.o: Shallow.cpp Shallow.h
	@${CC} ${CXXFLAGS} -c Shallow.cpp

main.o: main.cpp Shallow.h
	@${CC} ${CXXFLAGS} -c main.cpp

run:
	@./akash | lolcat

clean:
	@rm -f ${OBJS}

