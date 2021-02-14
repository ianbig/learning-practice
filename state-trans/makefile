CC = gcc
CFLAGS = -Wall
TARGET = main
OBJ = state.o main.o

all: ${TARGET}
main: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${TARGET}
state.o: state.c state.h
	${CC} ${CFLAGS} -c state.c
main.o: main.c
	${CC} ${CFLAGS} -c main.c
clean:
	rm ${OBJ}
	rm ${TARGET}
	rm state.log