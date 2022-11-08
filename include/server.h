#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "morse.h"
#include "delay.h"

#define LOG_LINE_LENGTH 100
#define BLOCKSIZE 1024

// SIGINT to exit cleanly and SIGCHLD to give client a bit more time (to write).
void sighandler_server(int sig);
