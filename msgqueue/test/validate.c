#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define MAXLOAD 100
#define MAXPATH 256
#define MAXBUF 256
#define NUM_Q 5

typedef struct {
    pid_t pid;
    char question[MAXLOAD];
    char answer[MAXLOAD];
    int validate;
} VALID_S;

typedef struct {
	char question[MAXLOAD];
	char answer[MAXLOAD];
} DB_S;

int extract_client(char buf[], VALID_S *vptr) {
    char *sptr;

    sptr = strtok(buf, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract client pid\n");
        return -1;
    }
    vptr->pid = atoi(sptr);

    sptr = strtok(NULL, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract client question\n");
        return -1;
    }
    sptr += strlen(" send question ");
    snprintf(vptr->question, sizeof(vptr->question), "%s", sptr);
    
    sptr = strtok(NULL, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract client question\n");
        return -1;
    }
    sptr += strlen(" receive answer is ");
    snprintf(vptr->answer, sizeof(vptr->answer), "%s", sptr);

    vptr->validate = 0;

    return 0;
}

int extract_server(char buf[], VALID_S *vptr) {
    char *sptr;
    int truncated_size = 0;

    sptr = strtok(buf, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract server pid\n");
        return -1;
    }
    sptr += strlen("Answer from ");
    vptr->pid = atoi(sptr);

    sptr = strtok(NULL, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract server question\n");
        return -1;
    }
    sptr += strlen(" receive question is ");
    snprintf(vptr->question, sizeof(vptr->question), "%s", sptr);

    sptr = strtok(NULL, ",");
    if(sptr == NULL) {
        fprintf(stderr, "Error: unexpected error in extract server answer\n");
        return -1;
    }
    sptr += strlen(" send answer is ");
    snprintf(vptr->answer, sizeof(vptr->answer), "%s", sptr);

    return 0;
}

int main(int argc, char *argv[]) {
    DIR *dir = NULL;
    char log[MAXPATH] = {0};
    struct dirent *entry = NULL;

    dir = opendir("./client_log");
    if(dir == NULL) {
        fprintf(stderr, "Error: cannot open directory\n");
        exit(EXIT_FAILURE);
    }

    errno = 0;
    VALID_S ** client_ptr = NULL;
    size_t client_query_num = 0, client_arr_capacity = 1;

    client_ptr = (VALID_S**)malloc(sizeof(VALID_S*) * client_arr_capacity);
    if(client_ptr == NULL) {
        fprintf(stderr, "Error: unable to malloc\n");
        exit(EXIT_FAILURE);
    }

    FILE *fptr = NULL;
    char buf[MAXBUF] = {0};
    struct stat st_buf;

    while((entry = readdir(dir)) != NULL ) {
        if(entry->d_name[0] - '.' == 0) {
            continue;
        }

        client_ptr[client_query_num] = (VALID_S*)malloc(sizeof(VALID_S) * 1);

        if(client_ptr[client_query_num] == NULL) {
            fprintf(stderr, "Error: unable to malloc");
            break;
        }

        snprintf(buf, sizeof(buf), "./client_log/%s", entry->d_name);
        if((fptr = fopen(buf, "r")) == NULL) {
            fprintf(stderr, "Error: unable to open folder %s\n", entry->d_name);
            continue;
        }

        stat(buf, &st_buf);
        memset(buf, 0, sizeof(buf));

        fread(buf, sizeof(char), st_buf.st_size, fptr);
        if(extract_client(buf, client_ptr[client_query_num]) == -1) {
            fprintf(stderr, "Error: broken content in %s\n", entry->d_name);
            continue;
        }
           
        memset(buf, 0, sizeof(buf));
        fclose(fptr);

        client_query_num++;

        if(client_query_num == client_arr_capacity) {
            client_arr_capacity = client_arr_capacity * 5;
            client_ptr = (VALID_S**)realloc(client_ptr, client_arr_capacity * sizeof(VALID_S*));
        }
    }

    fprintf(stderr, "query num is %ld\n", client_query_num);

    if(errno != 0 ) {
        fprintf(stderr, "Warning: unexpected behavior in parsing client log\n");
    }

    // // open info in server
    memset(log, 0 ,sizeof(log));
    fptr = fopen("./record.log", "r");

    if(fptr == NULL) {
        fprintf(stderr, "Error: cannot open server log\n");
        exit(EXIT_FAILURE);
    }

    size_t server_query_num = 0;
    int record_count = 0;
    char *line_ptr = NULL;
    size_t size = 0;
    VALID_S *server_ptr = NULL;

    while(getline(&line_ptr, &size, fptr) != -1) {
        record_count++;
    }

    free(line_ptr);
    line_ptr = NULL;
    fseek(fptr, 0, SEEK_SET);

    server_ptr = (VALID_S*)malloc(sizeof(VALID_S) * record_count);
    if(server_ptr == NULL) {
        fprintf(stderr, "Error: Heap size inadequate\n");
        exit(EXIT_FAILURE);
    }

    while (getline(&line_ptr, &size, fptr) != -1)
    {
        if( extract_server(line_ptr, &server_ptr[server_query_num]) == -1 ) {
            fprintf(stderr, "Error: broken content in server log\n");
            break; // still see how many queries is validated
        }
        server_query_num++;
    }

    free(line_ptr);
    fclose(fptr);

    int i = 0, j = 0;
    int validated_num = 0;
    for( i = 0; i < server_query_num; i ++) {
        for( j = 0; j < client_query_num; j++) {
            if(server_ptr[i].pid != client_ptr[j]->pid) {
                continue;
            }

            if(strcmp(server_ptr[i].question, client_ptr[j]->question) != 0) {
                continue;
            }

            if(strcmp(server_ptr[i].answer, client_ptr[j]->answer) != 0) {
                continue;
            }

            client_ptr[j]->validate = 1;
            // fprintf(stderr, "client %d is validated\n", client_ptr[j]->pid);
            validated_num++;
            break;
        }
    }

    int not_valid = 0;
    for(i = 0; i < client_query_num; i++) {
        if(client_ptr[i]->validate == 0) {
            fprintf(stderr, "=======Process id %d is not validate========\n", client_ptr[i]->pid);
            not_valid++;
        }
    }

    fprintf(stderr, "Number of validated: %d\n", validated_num);
    fprintf(stderr, "Number of not valid: %d\n", not_valid);

    for( i = 0; i < client_query_num; i++) {
        free(client_ptr[i]);
    }
    free(client_ptr);
    free(server_ptr);
    
    return 0;
}