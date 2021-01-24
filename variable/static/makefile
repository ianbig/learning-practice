CC = gcc
CFLAG = -Wall -Werror -std=c99

all:
global: global.o invalid_access.o header.h
	$(CC) $(CFLAG) global.o invalid_access.o -o global
function_scope: function.o invalid_access.o
	$(CC) $(CFLAG) function.o invalid_access.o -o function_scope
global.o: global.c
	$(CC) $(CFLAG) -c global.c
function.o: function.c
	$(CC) $(CFLAG) -c function.c
invalid_access.o: invalid_access.c
	$(CC) $(CFLAG) -c invalid_access.c
local: local.c
	$(CC) $(CFLAG) local.c -o local
clean:
	rm *.o global