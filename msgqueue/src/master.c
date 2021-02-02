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

void signalHandler() {
	main_loop = 0;
	printf("\n");
}

int main(int argc, char const *argv[]) {
	int msq_id = -1, i = 0;
	key_t key;

	MY_DATA_S data_rec;
	MY_DATA_S data_send;

	DB_S mydb;

	char file_path[MAX_FILE_NAME] = {0};
	char db_path[MAX_BYTES] = {0};
	char des_path[MAX_BYTES] = {0};
	unsigned int pid = getpid();
	int project_id = pid % 255;

	signal(SIGINT, signalHandler);

	getcwd(file_path, MAX_FILE_NAME);

	snprintf(des_path, MAX_BYTES, "%s/des.log", file_path);
	FILE *des_fptr = fopen(des_path, "w+");
	char logmsg[MAX_BYTES] = {0};

	if(des_fptr == NULL) {
		fprintf(stderr, "Error: Unexpect action in writing description log\n");
		exit(EXIT_FAILURE);
	}

	snprintf(logmsg, MAX_BYTES, "server_id:%d\nproject_path:%s\nproject_id:%d\n", pid, file_path, project_id);
	fwrite(logmsg, sizeof(char), strlen(logmsg), des_fptr);
	fflush(des_fptr);
	fclose(des_fptr);	
	
	DB_S **db = NULL;
	int db_size = 1;
	int question_num = 0;
	snprintf(db_path, MAX_BYTES, "%s/database.txt", file_path);
	FILE *db_fptr = fopen(db_path, "r");

	if(des_fptr == NULL) {
		fprintf(stderr, "Error: Unexpect action in open description log in master\n");
		exit(EXIT_FAILURE);
	}

	if( (db = (DB_S**)malloc(sizeof(DB_S*) * db_size)) == NULL ) {
		fprintf(stderr, "Error: Unexpected behavior in creating DB\n");
		exit(EXIT_FAILURE);
	}

	char *buf = NULL;
	size_t size = 0;
	int line_count = 0;
	int length = 0;

	while( (length = getline(&buf, &size, db_fptr)) != -1) {
		line_count++;

		if((line_count % 2) == 0) {
			if((db[question_num]->answer = (char*)malloc(sizeof(char) * (length + 1 ))) == NULL) {
				fprintf(stderr, "Error: malloc error\n");
				exit(EXIT_FAILURE);
			}
			snprintf(db[question_num]->answer, length + 1, "%s", buf);
			question_num++;

			if(question_num == db_size) {
				db_size = db_size * 5;
				db = (DB_S**)realloc(db, db_size * sizeof(DB_S*));
			}
		} else {
			db[question_num] = (DB_S*)malloc(sizeof(DB_S) * 1);

			if( (db[question_num]->question = (char*)malloc(sizeof(char) * (length + 1))) == NULL ) {
				fprintf(stderr, "Error: malloc error\n");
				exit(EXIT_FAILURE);
			}
			snprintf(db[question_num]->question, length + 1, "%s", buf);
			db[question_num]->question[length-1] = '\0';
		}
	}
	free(buf);

	fclose(db_fptr);

	key = ftok(file_path, project_id);

	if(key !=  -1) {
		if((msq_id = msgget(key, IPC_CREAT)) != -1 ) {
			fprintf(stderr, "Success create or connect to queue\n");
		} else {
			perror("Error in key:");
			exit(EXIT_FAILURE);
		}

		char r_path[MAX_BYTES] = {0};
		char record_buf[RECORD_MAX] = {0};
		snprintf(r_path, MAX_BYTES, "%s/record.log", file_path);
		FILE *r_fptr = fopen(r_path, "a+");

		fprintf(stderr, "=====Resolving for Request========\n");
		 while(main_loop) {
			if( msgrcv(msq_id, &data_rec, MAX_BYTES, pid, IPC_NOWAIT) != -1) {
				// fprintf(stderr, "Server receive message from process %lld\n", data_rec.msg.from);
				data_send.to = data_rec.msg.from;
				data_send.msg.from = data_rec.to;
				
				for(i = 0; i < question_num; i++) {
					if( strcmp(data_rec.msg.load, db[i]->question) == 0) {
						snprintf(data_send.msg.load, MAX_LOAD, "%s", db[i]->answer);
						break;
					} 
				}

				if( i == question_num ) {
					snprintf(data_send.msg.load, 20, "No such question\n");
				}
				
				if(!msgsnd(msq_id, &data_send, MAX_BYTES, IPC_NOWAIT)) {
					snprintf(record_buf, RECORD_MAX, "Answer from %lld, receive question is %s, send answer is %s", data_rec.msg.from, data_rec.msg.load, data_send.msg.load);
					fwrite(record_buf, sizeof(char), strlen(record_buf) +1, r_fptr);
					fflush(r_fptr);
					memset(record_buf, 0, sizeof(record_buf));
				} else {
					perror("Error: ");
					continue;
				}
			} else {
				if(errno == E2BIG) {
					fprintf(stderr, "receive type is too short\n");
					break;
				}
			}
		}
		
		fclose(r_fptr);
	} else {
		fprintf(stderr, "Error in generating key ......\n");
		exit(EXIT_FAILURE);
	}


	for(i = 0; i < question_num; i++) {
		free(db[i]->question);
		free(db[i]->answer);
		free(db[i]);
	}

	free(db);
	remove(des_path);
	msgctl(msq_id, IPC_RMID, NULL);
	
	return 0;
}
