#include <string.h>
#include "delay.h"
#include <unistd.h>
#include <signal.h>

#define DEFAULT_KILL_DELAY 500

// Converts a character to morse and possibly writes a log entry
char* morseEncode(char to_encode, int log_fd);

// Sends character to_send as morse to receiver and possibly writes a log entry
int sendCharInMorse(char to_send, pid_t receiver, int log_fd);

// Reads a character based on index and resets the ready flag
char readCharOfMorse(volatile int* index, volatile int* ready);
