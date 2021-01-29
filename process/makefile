CC = gcc
TARGET = main exit libso libso_static memory environ jump fork

all: $(TARGET)
exit: exit.c
	$(CC) exit.c -o exit
libso: libso.c
	$(CC) libso.c -o libso
libso_static: libso.c
	$(CC) -static libso.c -o libso_static
memory: memory.c
	$(CC) -Wall memory.c -o memory
environ: environ.c
	$(CC) environ.c -o environ
jump: jump.c
	$(CC) jump.c -o jump
fork: fork.c
	$(CC) fork.c -o fork
clean:
	rm $(TARGET)