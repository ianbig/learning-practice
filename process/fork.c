/*
	Test global would be change or not
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int global = 10;
char buf[] = "I am Ian, and I am handsome\n";

int main() {
	pid_t pid;

	if(write(STDIN_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
		fprintf(stderr, "Error in writing file\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Before forking\n");
	if( (pid = fork()) == -1 ) {
		perror("Error: ");
	}

	if(pid == 0) {
		global += 1;
	} else {
		global -= 1;
		sleep(2);
	}

	fprintf(stdout, "pid: %d global: %d\n", getpid(), global);
}