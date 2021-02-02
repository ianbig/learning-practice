CC = gcc
CC_LINARO = /opt/linaro-armv7ahf-2019.02-gcc7.4/bin/arm-linux-gnueabihf-gcc
TARGET_BOARD_MASTER = /mnt/share_folder/master 
TARGET_BOARD_CLIENT = /mnt/share_folder/client
TARGET_TEST = validate
SRC_MASTER = ./src/master.c
SRC_CLIENT = ./src/client.c
SRC_TEST = ./test/validate.c
TARGET = master client

all: ${TARGET}
master: ${SRC_MASTER}
	$(CC) ${SRC_MASTER} -o master
client: ${SRC_CLIENT}
	$(CC)  ${SRC_CLIENT} -o client
board: 
	$(CC_LINARO) ${SRC_MASTER} -o $(TARGET_BOARD_MASTER)
	$(CC_LINARO) ${SRC_CLIENT} -o $(TARGET_BOARD_CLIENT)
test: ${TARGET_TEST}
validate: ${SRC}
	$(CC) $(SRC_TEST) -o ${TARGET_TEST}
clean: 
	rm ${TARGET} ${TARGET_BOARD_MASTER} ${TARGET_BOARD_CLIENT} ${TARGET_TEST}