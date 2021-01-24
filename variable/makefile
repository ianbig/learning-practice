CC = gcc
TARGET = naming_convention_exec constant type_conversion register initial preprocessor
CFLAG = -g -Wall -Werror

all: $(TARGET)
naming_convention_exec: naming_convention.c
	$(CC) $(CFLAG) naming_convention.c -o naming_convention_exec
constant: constant.c
	$(CC) $(CFLAG) constant.c -o constant
type_conversion: type_conversion.c
	$(CC) $(CFLAG) type_conversion.c -o type_conversion
register: register.c
	$(CC) $(CFLAG) register.c -o register
initial: initial.c
	$(CC) initial.c -o initial
preprocessor: preprocessor.c
	$(CC) preprocessor.c -o preprocessor
clean:
	rm $(TARGET)