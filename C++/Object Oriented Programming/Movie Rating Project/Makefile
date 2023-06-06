CC=g++ 
CXXFLAGS= # -Wall -Wextra -Werror -std=c++20 -pedantic -ggdb
EXEC = akash
OBJS = Movie.o Movies.o main.o # List of object files needed to
MEMORY_SAFE_FLAGS= -fsanitize=address -fno-omit-frame-pointer

all: compile clean run

#@ for supressing the compilation messages
compile: ${OBJS}
	@${CC} ${CXXFLAGS} -o ${EXEC} ${OBJS} ${MEMORY_SAFE_FLAGS}

Movie.o: Movie.cpp Movie.h
	@${CC} ${CXXFLAGS} -c Movie.cpp

Movies.o: Movies.cpp Movies.h
	@${CC} ${CXXFLAGS} -c Movies.cpp

main.o: main.cpp Movie.h Movies.h
	@${CC} ${CXXFLAGS} -c main.cpp

run:
	@./akash | lolcat

clean:
	@rm -f ${OBJS}

