CC = gcc
CFLAG = -Wall -Werror -g -pthread
TARGET = deadlock deadlock_semaphore_tradition

all: $(TARGET)
deadlock: deadlock.c
	$(CC) $(CFLAG) deadlock.c -o deadlock
deadlock_semaphore_tradition: deadlock_semaphore_tradition.c
	$(CC) $(CFLAG) deadlock_semaphore_tradition.c -o deadlock_semaphore_tradition
clean:
	rm $(TARGET)