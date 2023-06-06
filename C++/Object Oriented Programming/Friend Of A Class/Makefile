CC=g++ 
CXXFLAGS=-Wall -Wextra -Werror -std=c++20 -pedantic -ggdb
EXEC = akash
OBJS = Player.o Friend_Class.o Other_Class.o main.o # List of object files needed to
MEMORY_SAFE_FLAGS= -fsanitize=address -fno-omit-frame-pointer

all: compile clean run

#@ for supressing the compilation messages
compile: ${OBJS}
	@${CC} ${CXXFLAGS} -o ${EXEC} ${OBJS} ${MEMORY_SAFE_FLAGS}

Player.o: Player.cpp Player.h
	@${CC} ${CXXFLAGS} -c Player.cpp

Friend_Class.o: Friend_Class.cpp Friend_Class.h
	@${CC} ${CXXFLAGS} -c Friend_Class.cpp

Other_Class.o: Other_Class.cpp Other_Class.h
	@${CC} ${CXXFLAGS} -c Other_Class.cpp

main.o: main.cpp Player.h Friend_Class.h Other_Class.h
	@${CC} ${CXXFLAGS} -c main.cpp

run:
	@./akash | lolcat

clean:
	@rm -f ${OBJS}

