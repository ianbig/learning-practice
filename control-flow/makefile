CC = gcc
CFLAG = -Wall -Werror
TARGET = switch do-while goto

all: $(TARGET)
switch: switch.c
	$(CC) $(CFLAG) switch.c -o switch
do-while: do-while.c
	$(CC) $(CFLAG) do-while.c -o do-while
goto: goto.c
	$(CC) $(CFLAG) goto.c -o goto
clean:
	rm $(TARGET)