CC = gcc
TARGET = extern extern_one_file

extern: extern.c
	$(CC) extern.c -o extern
extern_one_file: extern_one_file.c
	$(CC) extern_one_file.c -o extern_one_file

clean:
	rm $(TARGET)