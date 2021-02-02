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

typedef struct {
    pid_t pid;
    char question[MAXLOAD];
    char answer[MAXLOAD];
    int validate;
} VALID_S;

int extract_client(char buf[], VALID_S *vptr) {
    char *sptr;

    sptr = strtok(buf, ",");
    vptr->pid = atoi(sptr);

    sptr = strtok(NULL, ",");
    sptr += strlen(" send question ");
    snprintf(vptr->question, strlen(sptr) + 1, "%s", sptr);
    
    sptr = strtok(NULL, ",");
    sptr += strlen(" receive answer is ");
    snprintf(vptr->answer, strlen(sptr) + 1, "%s", sptr);
}

int main(int argc, char *argv[]) {
    DIR *dir = NULL;
    char working_dir[MAXPATH] = {0};
    char log_dir[MAXPATH] = {0};
    struct dirent *entry = NULL;

    if(getcwd(working_dir, MAXPATH) == NULL) {
        fprintf(stderr, "Error: unexpected behavior in getting directory\n");
        exit(EXIT_FAILURE);
    }

    snprintf(log_dir, MAXPATH + 15, "%s/client_log", working_dir);

    dir = opendir(log_dir);
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

        snprintf(buf, MAXBUF * 2 + 1, "%s/%s", log_dir, entry->d_name);
        if((fptr = fopen(buf, "r")) == NULL) {
            fprintf(stderr, "Error: unable to open folder %s\n", entry->d_name);
            continue;
        }

        stat(buf, &st_buf);
        memset(buf, 0, MAXBUF);

        fread(buf, sizeof(char), st_buf.st_size, fptr);
        extract_client(buf, client_ptr[client_query_num]);   
             
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

    int i = 0;
    for( i; i < client_query_num; i++) {
        free(client_ptr[i]);
    }
    free(client_ptr);
}