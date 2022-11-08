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
#define BLOCKSIZE 1024
#define DEFAULT_KILL_DELAY 500
#define LOG_LINE_LENGTH 100
#define DEFAULT_LOG "log.txt"

// FUNCTION DEFINITIONS

char* morseEncode(char, int);

int sendCharInMorse(char, pid_t, int);

char readCharOfMorse(volatile int*, volatile int*);

void sighandler_client(int);

void sighandler_server(int);

void delay_micro(int);
