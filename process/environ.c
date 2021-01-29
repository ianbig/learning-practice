/*
	Function about environment variable
	1. life cycle of a environment created by putenv only exist when process is alive
*/
#include <stdio.h>
#include <stdlib.h>


int main() {

	fprintf(stderr, "my env variable is %s\n", getenv("HOME"));

	// set an env variable
	if ( !putenv("IAN=/home/ianbigass") ) {
		fprintf(stderr, "my env variable is %s\n", getenv("IAN"));
	} else {
		fprintf(stderr, "Error is setting environment variable\n");
	}

	if( !setenv("IAN", "/home/ianbigassdump", 1) ) {
		fprintf(stderr, "my env variable is %s\n", getenv("IAN"));
	} else {
		fprintf(stderr, "Error is setting environment variable\n");
	}
	// if name exist, the variable would not be overwrite
	if( !setenv("IAN", "/home/ianbigassdump_123", 0) ) {
		fprintf(stderr, "my env variable is %s\n", getenv("IAN"));
	} else {
		fprintf(stderr, "Error is setting environment variable\n");
	}
	// if name is not exist, it would also return 0
	if( !unsetenv("IAN") ) {
		fprintf(stderr, "my env variable is %s\n", getenv("IAN"));
	} else {
		fprintf(stderr, "variable name not exist\n");
	}

	return 0;	
	
}