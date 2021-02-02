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

typedef struct {
    pid_t pid;
    char question[MAXLOAD];
    char answer[MAXLOAD];
    int validate;
} VALID_S;

void extract_client(char buf[], VALID_S *vptr) {
    char *sptr;

    sptr = strtok(buf, ",");
    vptr->pid = atoi(sptr);

    sptr = strtok(NULL, ",");
    sptr += strlen(" send question ");
    snprintf(vptr->question, MAXLOAD, "%s", sptr);
    
    sptr = strtok(NULL, ",");
    sptr += strlen(" receive answer is ");
    snprintf(vptr->answer, MAXLOAD, "%s", sptr);

    vptr->validate = 0;

}

void extract_server(char buf[], VALID_S *vptr) {
    char *sptr;

    sptr = strtok(buf, ",");
    sptr += strlen("Answer from ");
    vptr->pid = atoi(sptr);

    sptr = strtok(NULL, ",");
    sptr += strlen(" receive question is ");
    snprintf(vptr->question, MAXLOAD, "%s", sptr);

    sptr = strtok(NULL, ",");
    sptr += strlen(" send answer is ");
    snprintf(vptr->answer, MAXLOAD, "%s"m sptr);
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

        snprintf(buf, MAXBUF * 2 + 1 + 1, "%s/%s", log_dir, entry->d_name);
        if((fptr = fopen(buf, "r")) == NULL) {
            fprintf(stderr, "Error: unable to open folder %s\n", entry->d_name);
            continue;
        }

        stat(buf, &st_buf);
        memset(buf, 0, MAXBUF);

        fread(buf, sizeof(char), st_buf.st_size, fptr);
        extract_client(buf, client_ptr[client_query_num]);   

        memset(buf, 0, MAXBUF)
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

    // open info in server
    memset(log_dir, 0 ,MAXPATH);
    memset(st_buf, 0, sizeof(struct stat));

    snprintf(log_dir, MAXPATH, "%s/record.log", working_dir);
    fptr = fopen(log_dir, "r");

    if(fptr == NULL) {
        fprintf(stderr, "Error: cannot open server log"\n);
        exit(EXIT_FAILURE);
    }

    stat(log_dir, &st_buf);
    fread(buf, sizeof(char), st_buf.st_size, fptr);

    char *line_ptr = NULL;
    size_t size = 0;
    VALID_S **server_ptr = NULL;
    size_t server_capacity = 1;
    size_t server_query_num = 0;

    server_ptr = (VALID_S**)malloc(sizeof(VALID_S*) * server_capacity);
    if(server_ptr == NULL) {
        fprintf(stderr, "Error: unable to malloc memory for server\n");
        exit(EXIT_FAILURE);
    }

    while(getline(&line_ptr, &size, fptr) != NULL) {
        extract_server(line_ptr, server_ptr[server_query_num]);
        server_query_num++;

        if(server_query_num == server_capacity) {
            server_capacity *= 5;
            server_ptr = (VALID_S**)realloc(server_ptr, sizeof(VALID_S*) * server_capacity);
        }
    }
    free(line_ptr);

    int i = 0, j = 0;;
    // compare server and client
    for( i = 0; i < server_query_num; i ++) {
        for( j = 0; j < client_query_num; j++) {
            if(server_ptr[i]->pid != client_ptr[j]->pid) {
                continue;
            }

            if(strcmp(server_ptr[i]->question, client_ptr[j]->question) != 0) {
                continue
            }

            if(strcmp(server_ptr[i]->answer, client_ptr[j]->answer) != 0) {
                continue
            }

            client_ptr[j]->validate = 1;
            break;
        }
    }
    // print out not handle client
    for(i = 0; i < client_query_num; i++) {
        if(client_ptr[i]->validate == 0) {
            fprintf(stderr, "=======Process id %d is not validate========\n", client_ptr[i]->pid);
        }
    }

    for( i; i < client_query_num; i++) {
        free(client_ptr[i]);
    }
    free(client_ptr);

    for(i = 0; i < server_query_num; i++) {
        free(server_ptr);
    }
    free(server_ptr);
    
}