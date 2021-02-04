CC = gcc
CC_LINARO = /opt/linaro-armv7ahf-2019.02-gcc7.4/bin/arm-linux-gnueabihf-gcc 
TARGET_BOARD_MASTER = /mnt/share_folder/master 
TARGET_BOARD_CLIENT = /mnt/share_folder/client
TARGET_BOARD_TEST = /mnt/share_folder/validate
TARGET_TEST = validate
SRC_MASTER = ./src/master.c
SRC_CLIENT = ./src/client.c
SRC_TEST = ./test/validate.c
TARGET = master client

all: ${TARGET}
master: ${SRC_MASTER}
	$(CC) ${SRC_MASTER} -g -o master
client: ${SRC_CLIENT}
	$(CC)  ${SRC_CLIENT} -g -o client
board: 
	$(CC_LINARO) ${SRC_MASTER} -std=c99 -o $(TARGET_BOARD_MASTER)
	$(CC_LINARO) ${SRC_CLIENT} -std=c99 -o $(TARGET_BOARD_CLIENT)
	$(CC_LINARO) ${SRC_TEST} -o ${TARGET_BOARD_TEST}
test: ${TARGET_TEST}
validate: ${SRC_TEST}
	$(CC) $(SRC_TEST) -o ${TARGET_TEST}
clean: 
	rm ${TARGET} ${TARGET_BOARD_MASTER} ${TARGET_BOARD_CLIENT} ${TARGET_TEST}
cleanlog:	
	rm -f ./client_log/*.log record.log
