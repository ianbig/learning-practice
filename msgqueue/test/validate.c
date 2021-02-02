#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define MAXLOAD 100

typedef struct {
    pid_t pid;
    char question[MAXLOAD];
    char answer[MAXLOAD];
    int validate;
}

int main(int argc, char *argv[]) {

}