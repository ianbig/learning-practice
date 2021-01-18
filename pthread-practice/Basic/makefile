CC = gcc
CFLAG = -Wall -Werror -g -pthread
TARGET = no-lock semaphore mutex

all: $(TARGET)
no-lock: no-lock.c
	$(CC) $(CFLAG) no-lock.c -o no-lock
semaphore: semaphore.c
	$(CC) $(CFLAG) semaphore.c -o semaphore
mutex: mutex.c
	$(CC) $(CFLAG) mutex.c -o mutex

clean:
	rm $(TARGET)