CC = gcc
OBJ = source.o extern.o
TARGET = test

all: $(TARGET)
test: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
source.o: source.c
	$(CC) -c source.c
extern.o: extern.c
	$(CC) -c extern.c

clean:
	rm source.o extern.o