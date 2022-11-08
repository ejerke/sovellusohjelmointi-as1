#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "morse.h"
#include "delay.h"

#define LOG_LINE_LENGTH 100
#define BLOCKSIZE 1024

// SIGUSR1 and SIGUSR2 increment char_index, SIGALRM sets char_ready, SIGINT exits
void sighandler_client(int);
