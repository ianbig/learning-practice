#ifndef STRUCT_H
#define STRUCT_H

#define MAX_BYTES 512
#define MAX_FILE_NAME 256
#define RECORD_MAX 512 * 3
#define MAXLOAD 100

typedef struct {
	long from;
	char load[MAXLOAD];
} MY_CONTENT_S;

typedef struct {
	long to;
	MY_CONTENT_S msg;
} MY_DATA_S;

typedef struct {
	char question[MAXLOAD];
	char answer[MAXLOAD];
} DB_S;

#endif