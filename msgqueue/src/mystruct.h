#ifndef STRUCT_H
#define STRUCT_H

#define MAX_BYTES 512
#define MAX_FILE_NAME 256
#define RECORD_MAX 512 * 3
#define MAX_LOAD 100

typedef struct {
	long long from;
	char load[MAX_LOAD];
} MY_CONTENT_S;

typedef struct {
	long long to;
	MY_CONTENT_S msg;
} MY_DATA_S;

typedef struct {
	char *question;
	char *answer;
} DB_S;

typedef struct {
	char *question;
	char *answer;
	pid_t incomming_id;
} RECORD_S;

#endif