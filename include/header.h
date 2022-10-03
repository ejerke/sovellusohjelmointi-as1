
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
#define END_KILL_DELAY 400

// FUNCTION DEFINITIONS

char* morseEncode(char);

int sendCharInMorse(char, pid_t);

char readCharOfMorse(void);

void sighandler_client(int);

void delay_micro(int);