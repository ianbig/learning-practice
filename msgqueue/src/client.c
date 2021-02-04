#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "mystruct.h"

typedef struct {
	key_t key;
	pid_t server_id;
} CONFIG_S;


int config_description_log(CONFIG_S *config) {

	char buf[MAX_BYTES] = {0};
	int file_size = 0;
	int msq_id = 0;

	FILE *fptr = fopen("./des.log", "r");

	if(fptr == NULL) {
		fprintf(stderr, "Error: no description log or description log closed\n");
		exit(EXIT_FAILURE); // no description log means master is closed
	}

	fseek(fptr, 0, SEEK_END);
	file_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	fread(buf, sizeof(char), file_size, fptr);

	char *ptr = NULL, *endptr = NULL;

	ptr = strchr(buf, ':');
	endptr = strchr(buf, '\n');
	if(ptr == NULL || endptr == NULL) {
		fprintf(stderr, "Error: unexpected error in description log\n");
		return -1;
	}
	*endptr = '\0';
	config->key = atoi(ptr+1);

	ptr = endptr + 1;
	ptr = strchr(ptr, ':');
	if(ptr == NULL) {
		fprintf(stderr, "Error: unexpected error in description log\n");
		return -1;
	}
	endptr = strchr(ptr, '\n');
	if(endptr == NULL) {
		fprintf(stderr, "Error: unexpected error in description log\n");
		return -1;
	}
	*endptr = '\0';
	config->server_id = atoi(ptr+1);

	// fprintf(stderr, "key: %d\nserver_id: %d\n", config->key, config->server_id);

	return 0;
}

int main(int argc, char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: ./client [question type]\n");
		exit(EXIT_FAILURE);
	}

	CONFIG_S config;
	config_description_log(&config);

	pid_t pid = getpid();
	MY_DATA_S data_rec;
	MY_DATA_S data_send;

	char file_path[MAX_FILE_NAME] = {0};
	snprintf(file_path, sizeof(file_path), "./client_log/%d.log", pid);
	FILE *rec_fptr = fopen(file_path, "w+");

	if(rec_fptr == NULL) {
		fprintf(stderr, "Error: unable create client %d's log\n", pid);
		exit(EXIT_FAILURE);
	}

	int msq_id;
	if(config.key != -1) {
		if( (msq_id = msgget(config.key, IPC_CREAT)) != -1) {
			fprintf(stderr, "Connecting to msq id: %d\n", msq_id);

			data_send.to = config.server_id;
			data_send.msg.from = pid;
			snprintf(data_send.msg.load, sizeof(data_send.msg.load), "%s", argv[1]);

			if(!msgsnd(msq_id, &data_send, sizeof(data_send.msg.load), IPC_NOWAIT)) {
				fprintf(stderr, "client pid %d sent to queue\n", pid);
				if(msgrcv(msq_id, &data_rec, sizeof(data_send.msg.load), pid, 0) != -1) {
					fprintf(stderr, "==========\nClient process %d\nQuestion: %s\nAnswer: %s\n", \
					pid, argv[1], data_rec.msg.load);
					fprintf(rec_fptr, "%d, send question %s, receive answer is %s\n", \
					pid, argv[1], data_rec.msg.load);
				} else {
					fprintf(stderr, "Error: message queue is closed\n");
					perror("Error: Client cannot connect to msq");
				}
			} else {
				fprintf(stderr, "Error: client unable to send message\n");
			}
		} else {
			fprintf(stderr, "Error: unable to connect to queue of associated key");
		}

	} else {
		fprintf(stderr,"ERROR in client to obtain key: ");
		exit(EXIT_FAILURE);
	}

	fclose(rec_fptr);
	return 0;
}

