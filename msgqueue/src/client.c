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

int main(int argc, char **argv) {

	struct stat st_buf;
	char working_dir[MAX_FILE_NAME] = {0};
	char file_path[MAX_BYTES] = {0};

	if(argc != 2) {
		fprintf(stderr, "Usage: ./client [question type]\n");
		exit(EXIT_FAILURE);
	}

	if(getcwd(working_dir, MAX_FILE_NAME) == NULL) {
		fprintf(stderr, "Error: unable to get working directory\n");
		exit(EXIT_FAILURE);
	}
	snprintf(file_path, MAX_BYTES, "%s/des.log", working_dir);

	FILE *des_fptr = fopen(file_path, "r");

	if(des_fptr == NULL) {
		fprintf(stderr, "Error: no description log or description log closed\n");
		return 0; // no description log means master is closed
	}

	if(stat(file_path, &st_buf) == -1) {
		fprintf(stderr, "Error: unable to read description log stat\n");
		exit(EXIT_FAILURE); // since cannot get key
	}

	char *lineptr = NULL;
	char *mvptr = NULL;
	size_t size = 0;
	unsigned int project_id = 0;
	char project_path[MAX_BYTES] = {0};
	unsigned int server_id = 0;

	while( getline(&lineptr, &size, des_fptr) != -1 ) {
		if( (mvptr = strtok(lineptr, ":")) != NULL) {
			mvptr += strlen(mvptr) + 1;
			mvptr[strlen(mvptr)-1] = '\0';
			
			if(strcmp(lineptr, "project_path") == 0) {
				snprintf(project_path, strlen(mvptr) + 1, "%s", mvptr);
			} else if(strcmp(lineptr, "project_id") == 0) {
				project_id = atoi(mvptr);
			} else if(strcmp(lineptr, "server_id") == 0) {
				server_id = atoi(mvptr);
			}else {
				fprintf(stderr, "Error: wrong file indicator %s\n", lineptr);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "Error: wrong format in description log\n");
			exit(EXIT_FAILURE);
		}
	}

	free(lineptr);
	lineptr = NULL;
	fclose(des_fptr);
	memset(file_path, 0, MAX_BYTES);

	int msq_id;
	key_t key;
	pid_t pid;
	char record_buf[RECORD_MAX] = {0};

	MY_DATA_S data_rec;
	MY_DATA_S data_send;

	size = 0;
	key = ftok(project_path, project_id);
	pid = getpid();

	snprintf(file_path, MAX_FILE_NAME + strlen("/client_log/n.log"), "%s/client_log/%d.log", working_dir, pid);
	FILE *rec_fptr = fopen(file_path, "w+");

	if(rec_fptr == NULL) {
		fprintf(stderr, "Error: unable create client %d's log\n", pid);
		exit(EXIT_FAILURE);
	}

	if(key != -1) {
		if( (msq_id = msgget(key, IPC_CREAT)) != -1) {
			// fprintf(stderr, "Connecting to msq id: %d\n", msq_id);

			data_send.to = server_id;
			data_send.msg.from = pid;
			snprintf(data_send.msg.load, MAX_LOAD, "%s", argv[1]);

			if(!msgsnd(msq_id, &data_send, MAX_BYTES, IPC_NOWAIT)) {
				// fprintf(stderr, "client pid %d sent to queue\n", pid);
				if(msgrcv(msq_id, &data_rec, MAX_BYTES, pid, 0) != -1) {
					fprintf(stderr, "==========\nClient process %d\nQuestion: %s\nAnswer: %s", \
					pid, argv[1], data_rec.msg.load);

					snprintf(record_buf, RECORD_MAX, "%d, send question %s, receive answer is %s", \
					pid, data_send.msg.load, data_rec.msg.load);
					fwrite(record_buf, sizeof(char), strlen(record_buf), rec_fptr);
					memset(record_buf, 0, RECORD_MAX);
				} else {
					fprintf(stderr, "Error: message queue is closed\n");
					//perror("Error: ");
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

	return 0;
}

