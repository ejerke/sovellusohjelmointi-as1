
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
#define DEFAULT_KILL_DELAY 100
#define END_KILL_DELAY 1000

// FUNCTION DEFINITIONS

// int ChildProcess();

// int ParentProcess();

char* morseEncode(char a);

int sendCharInMorse(char a, pid_t target);

void sighandler_client(int);

void delay_micro(int seconds);