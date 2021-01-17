CC = gcc
TARGET = naming_convention_exec constant type_conversion
CFLAG = -g -Wall -Werror

all: $(TARGET)
naming_convention_exec: naming_convention.c
	$(CC) $(CFLAG) naming_convention.c -o naming_convention_exec
constant: constant.c
	$(CC) $(CFLAG) constant.c -o constant
type_conversion: type_conversion.c
	$(CC) $(CFLAG) type_conversion.c -o type_conversion
clean:
	rm $(TARGET)