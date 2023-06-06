CC=g++ 
CXXFLAGS= -std=c++20 -pedantic -ggdb
EXEC = akash
OBJS = Player.o main.o # List of object files needed to
MEMORY_SAFE_FLAGS= -fsanitize=address -fno-omit-frame-pointer

all: compile clean run

#@ for supressing the compilation messages
compile: ${OBJS}
	@${CC} ${CXXFLAGS} -o ${EXEC} ${OBJS} ${MEMORY_SAFE_FLAGS}

Player.o: Player.cpp Player.h
	@${CC} ${CXXFLAGS} -c Player.cpp 

main.o: main.cpp Player.h
	@${CC} ${CXXFLAGS} -c main.cpp 

run:
	@./akash | lolcat

clean:
	@rm -f ${OBJS}

