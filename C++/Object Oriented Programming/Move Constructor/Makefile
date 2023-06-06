CC=g++ 
CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -pedantic -ggdb
EXEC = akash
OBJS = Move.o main.o # List of object files needed to
MEMORY_SAFE_FLAGS= -fsanitize=address -fno-omit-frame-pointer

all: compile clean run

#@ for supressing the compilation messages
compile: ${OBJS}
	@${CC} ${CXXFLAGS} -o ${EXEC} ${OBJS} ${MEMORY_SAFE_FLAGS}

Move.o: Move.cpp Move.h
	@${CC} ${CXXFLAGS} -c Move.cpp

main.o: main.cpp Move.h
	@${CC} ${CXXFLAGS} -c main.cpp

run:
	@./akash | lolcat

clean:
	@rm -f ${OBJS}

