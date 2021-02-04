#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include "mystruct.h"


/*
	Testing:
		* what happen to client's msgsnd when the queue is full
		* what happen to msgsnd if queue is not exist
		* key_t set to IPC_PRIVATE, and reopen an msg queue
		* key_t is not IPC_PRIVATE
*/

/*
	Successfully Test
		* Queue message would pop out if ,msgrcv is called
		* what happen to msgsnd if queue is not exist: message queue would be created
		* if key_t is ipcs it would continue to open an queue with key 0x00000
*/

int main_loop = 1;
DB_S *db = NULL;

void signalHandler() {
	main_loop = 0;
	printf("\n");
}

key_t create_log(pid_t pid) {
	int project_id = pid % 255;
	project_id = 1;
	key_t key = 0;
	FILE *fptr = fopen("./des.log", "w");
	key = ftok("./des.log", project_id);

	if(fptr == NULL) {
		fprintf(stderr, "Error: Unexpect action in writing description log\n");
		return -1;
	}

	fprintf(fptr, "key:%d\nserver_pid:%d\n", key, pid);

	fclose(fptr);

	return key;
}

int setup_db() {
	FILE *fptr;
	int db_size = 0;
	char *buf = NULL;
	fptr = fopen("database.txt", "r");

	if(fptr == NULL) {
		fprintf(stderr, "Error: Unexpect action in open description log in master\n");
		exit(EXIT_FAILURE);
	}

	fseek(fptr, 0, SEEK_END);
	db_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	buf = (char*)malloc(sizeof(char) * (db_size + 1));
	if(buf == NULL) {
		fprintf(stderr, "Error: malloc error\n");
		return -1;
	}

	fread(buf, sizeof(char), db_size, fptr);
	buf[db_size] = '\0';

	int count = 0;
	int set_count = 0;
	char *ptr = NULL;
	while((ptr = strchr(buf, '\n') )!= NULL) {
		count++;
		if(count % 2 == 0) {
			*ptr = '.';
			set_count++;
		} else {
			*ptr = '?';
		}
	}
	fclose(fptr);

	db = (DB_S*)malloc(sizeof(DB_S) * set_count);
	if(db == NULL) {
		fprintf(stderr, "Error: unable to malloc\n");
		return -1;
	}

	int index = 0;
	char *preptr = buf;
	int copy_size = 0;
	count = 1;
	while(index + 1 <= set_count) {
		if(count % 2 == 0) {
			ptr = strchr(buf, '.');
			*ptr = '\n';
			copy_size = ptr - preptr;
			snprintf(db[index].answer, copy_size + 1, "%s", preptr);
			preptr = ptr + 1;
			index++;
		} else {
			ptr = strchr(buf, '?');
			*ptr = '\n';
			copy_size = ptr - preptr;
			snprintf(db[index].question, copy_size + 1, "%s", preptr);
			preptr = ptr + 1;
		}
		count++;
	}

	free(buf);

	return set_count;
}

int main(int argc, char const *argv[]) {
	signal(SIGINT, signalHandler);

	int question_num = -1;
	int i =0;

	question_num = setup_db();
	if(question_num == -1) {
		fprintf(stderr, "Error: unexpected behavior in create db");
		exit(EXIT_FAILURE);
	}

	pid_t pid = getpid();
	int project_id = pid % 255;
	key_t key = 0;
	int msq_id = -1;
	MY_DATA_S data_rec, data_send;
	FILE *fptr = NULL;

	key = create_log(pid);

	if(key !=  -1) {
		if((msq_id = msgget(key, IPC_CREAT)) != -1 ) {
			fprintf(stderr, "Success create or connect to queue\n");
		} else {
			perror("Error in key:");
			exit(EXIT_FAILURE);
		}

		fptr = fopen("./record.log", "a");
		if(fptr == NULL) {
			fprintf(stderr, "Error: unable to open record log\n");
			exit(EXIT_FAILURE);
		}

		fprintf(stderr, "=====Server pid %d on========\n", pid);
		 while(main_loop) {
			if( msgrcv(msq_id, &data_rec, sizeof(data_rec.msg.load), pid, IPC_NOWAIT) != -1) {
				// fprintf(stderr, "Server receive message from process %lld\n", data_rec.msg.from);
				data_send.to = data_rec.msg.from;
				data_send.msg.from = data_rec.to;

				for(i = 0; i < question_num; i++) {
					if( strcmp(data_rec.msg.load, db[i].question) == 0) {
						snprintf(data_send.msg.load, sizeof(data_send.msg.load), "%s", db[i].answer);
						break;
					} 
				}

				if( i == question_num ) {
					snprintf(data_send.msg.load, sizeof(data_send.msg.load), "No such question\n");
				}

				if(!msgsnd(msq_id, &data_send, sizeof(data_send.msg.load), IPC_NOWAIT)) {
					fprintf(fptr, "Answer from %ld, receive question is %s, send answer is %s\n", data_rec.msg.from, data_rec.msg.load, data_send.msg.load);
					fflush(fptr);
				} else {
					perror("Error: Server not send ");
					continue;
				}
			} else {
				if(errno == E2BIG) {
					fprintf(stderr, "receive type is too short\n");
					break;
				}

			}
		}
		fclose(fptr);
	} else {
		fprintf(stderr, "Error in generating key ......\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Outside loop\n");
	free(db);
	fprintf(stderr, "Outside loop\n");
	remove("./des.log");
	fprintf(stderr, "Outside loop\n");
	msgctl(msq_id, IPC_RMID, NULL);
	fprintf(stderr, "Outside loop\n");
	
	return 0;
}
