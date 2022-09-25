
// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// CONSTANT DEFINITIONS
#define BLOCKSIZE 4096
#define MAX_COUNT 5


// FUNCTION DEFINITIONS

// int ChildProcess();

// int ParentProcess();

void sighandler_client(int);

void delay(int seconds);