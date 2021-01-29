#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BYTES 512
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
*/

typedef struct {
	long long from;
	char load[MAX_BYTES];
} MY_CONTENT_S;

typedef struct {
	long long to;
	MY_CONTENT_S msg;
} MY_DATA_S;

typedef struct {
	char *question;
	char *answer;
} DB_S;

int main(int argc, char const *argv[]) {
	int msq_id;
	key_t key;
	struct msqid_ds msq_buf;

	MY_DATA_S data_rec;
	MY_DATA_S data_send;

	DB_S mydb;


	key = ftok("/mymount", 1);

	FILE *fptr = fopen("/mymount/database.txt", "r");

	if(fptr == NULL) {
		fprintf(stderr, "Error: Unexpect action in open database\n");
		perror("Error: ");
		exit(EXIT_FAILURE);
	}

	char *buf = NULL;
	size_t size = 0;
	int line_count = 0;
	int length = 0;
	int index
	while( (length = getline(&buf, &size, fptr)) != -1) {
		line_count++;
		buf[length - 1] = '\0';
		
		if( (line_count % 2) == 0 ) {

		}

		free(buf);
		buf = NULL;
	}

	/*if(key !=  -1) {
		if((msq_id = msgget(key, IPC_CREAT)) != -1 ) {
			fprintf(stderr, "Success create or connect to queue\n");
			// create description file
		} else {
			perror("Error in key:");
			exit(EXIT_FAILURE);
		}

		if(msgctl(msq_id, IPC_STAT, &msq_buf) == -1) {
			perror("Error");
			exit(EXIT_FAILURE);
		}
		
		fprintf(stderr, "=====Resolving for Request========\n");
		 while(1) {
			if( msgrcv(msq_id, &data_rec, MAX_BYTES, 1, IPC_NOWAIT) != -1) {
				fprintf(stderr, "Server is handling message type: %lld Content: %s\n", data_rec.msg.from ,data_rec.msg.load);
				
				data_send.to = data_rec.msg.from;
				data_send.msg.from = data_rec.to;
				fprintf(stderr, "send back type %lld\n", data_send.to);
				snprintf(data_send.msg.load, MAX_BYTES, "I get your request, here is your response from server");

				if(!msgsnd(msq_id, &data_send, MAX_BYTES, IPC_NOWAIT)) {
					fprintf(stderr, "Send Back Request\n");	
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
	} else {
		fprintf(stderr, "Error in generating key ......\n");
		exit(EXIT_FAILURE);
	}*/
	
	return 0;
}