CC = gcc
CC_LINARO = /opt/linaro-armv7ahf-2019.02-gcc7.4/bin/arm-linux-gnueabihf-gcc
TARGET_BOARD_MASTER = /mnt/share_folder/master 
TARGET_BOARD_CLIENT = /mnt/share_folder/client
TARGET = master client

all: $(TARGET)
master: master.c
	$(CC) master.c -o master
client: client.c
	$(CC) client.c -o client
board: $(TARGET_BOARD)
	$(CC_LINARO) master.c -o $(TARGET_BOARD_MASTER)
	$(CC_LINARO) client.c -o $(TARGET_BOARD_CLIENT)
clean: 
	rm $(TARGET) $(TARGET_BOARD_MASTER) $(TARGET_BOARD_CLIENT)