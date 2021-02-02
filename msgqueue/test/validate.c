#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define MAXLOAD 100
#define MAXPATH 256

typedef struct {
    pid_t pid;
    char question[MAXLOAD];
    char answer[MAXLOAD];
    int validate;
} VALID_S;

int main(int argc, char *argv[]) {
    DIR *dir = NULL;
    char working_dir[MAXPATH] = {0};
    char log_dir[MAXPATH] = {0};
    struct dirent *entry = NULL;

    if(getcwd(working_dir, MAXPATH) == NULL) {
        fprintf(stderr, "Error: unexpected behavior in getting directory\n");
        exit(EXIT_FAILURE);
    }

    snprintf(log_dir, MAXPATH, "%s/client_log", working_dir);

    dir = opendir(log_dir);
    if(dir == NULL) {
        fprintf(stderr, "Error: cannot open directory");
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

    while((entry = readdir(dir)) != NULL) {
        client_ptr[client_query_num] = (VALID_S*)malloc(sizeof(VALID_S) * 1);

        if(client_ptr[client_query_num] == NULL) {
            fprintf(stderr, "Error: unable to malloc");
            break;
        }

        if(client_query_num == client_arr_capacity) {
            client_arr_capacity = client_arr_capacity * 5;
            client_ptr = (VALID_S**)realloc(client_ptr, client_arr_capacity);
        }
    }

    if(errno != 0 ) {
        fprintf(stderr, "Warning: unexpected behavior in parsing client log\n");
    }

    int i = 0;
    for( i; i < client_query_num; i++) {
        free(client_ptr[i]);
    }
    free(client_ptr);
}