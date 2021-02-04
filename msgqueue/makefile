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
BOARD_TARGET = ${TARGET_BOARD_MASTER} ${TARGET_BOARD_CLIENT} ${TARGET_BOARD_TEST}

all: ${TARGET}
master: ${SRC_MASTER}
	$(CC) ${SRC_MASTER} -o master
client: ${SRC_CLIENT}
	$(CC)  ${SRC_CLIENT} -o client

test: ${TARGET_TEST}
validate: ${SRC_TEST}
	$(CC) $(SRC_TEST) -o ${TARGET_TEST}

board: ${BOARD_TARGET}
$(TARGET_BOARD_MASTER): ${SRC_MASTER}
	$(CC_LINARO) ${SRC_MASTER} -o $(TARGET_BOARD_MASTER)
${TARGET_BOARD_CLIENT}: ${SRC_CLIENT}
	$(CC_LINARO) ${SRC_CLIENT} -o $(TARGET_BOARD_CLIENT)
${TARGET_BOARD_TEST}: ${SRC_TEST}
	$(CC_LINARO) ${SRC_TEST} -o ${TARGET_BOARD_TEST}

clean: 
	rm ${TARGET} ${TARGET_BOARD_MASTER} ${TARGET_BOARD_CLIENT} ${TARGET_TEST} ${TARGET_BOARD_TEST}
cleanlog:	
	rm -f ./client_log/*.log record.log
