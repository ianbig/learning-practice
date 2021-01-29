#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

#define MAX_BYTES 512
#define SERVER_MSG_TYPE 1L // since pid 1 is init process this can guarantee client pid would not be 1

typedef struct {
	long long from;
	char load[MAX_BYTES];
} MY_CONTENT_S;

typedef struct {
	long long to;
	MY_CONTENT_S msg;
} MY_DATA_S;

int main() {
	int msq_id;
	key_t key;
	long pid;

	MY_DATA_S data_rec;
	MY_DATA_S data_send;

	key = ftok("/mymount", 1);
	pid = getpid();
	// key = ftok("/home/ian/learning-practice/msgqueue", 1);

	if(key != -1) {
		if( (msq_id = msgget(key, IPC_CREAT)) != -1) {
			fprintf(stderr, "Connecting to msq id: %d\n", msq_id);
			data_send.to = SERVER_MSG_TYPE;
			data_send.msg.from = pid;
			snprintf(data_send.msg.load, MAX_BYTES, "Client Request");
			if(!msgsnd(msq_id, &data_send, MAX_BYTES, IPC_NOWAIT)) {
				if(msgrcv(msq_id, &data_rec, MAX_BYTES, pid, 0) != -1) {
					fprintf(stderr, "Client receive %s\n", data_rec.msg.load);
				} else {
					fprintf(stderr, "Error: Unable to receive message\n");
					perror("Error: ");
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

// what do type in struct do