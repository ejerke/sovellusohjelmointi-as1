#include "header.h"

static char text[BLOCKSIZE];
static volatile int text_i = 0;

static const char *letter = "**etianmsurwdkgohvf?l?pjbxcyzq??54$3?? 2.,+-_??16=/?????7???8\n90";

static volatile int char_index = 1;
static volatile int char_ready = 0;
static volatile int should_continue = 1;

int main(int argc, char **argv)
{
	// pid_t parent_id = getppid();
	memset(text, 0, sizeof(text));
	int ofd;
	int log_fd = strtol(argv[1], NULL, 10);
	write(log_fd, "Client has access to log file\n", 30);

	// Start gives output file to client either as dash (stdout) or a filename.
	if ( !strcmp(argv[0],"-") )
    	 ofd = STDOUT_FILENO;
	else
		ofd = creat(argv[0], 0666);

	write(log_fd, "**Output fd established from argv[0]\n", 37);

	// Start listening to signals

	struct sigaction act;
	act.sa_handler = &sighandler_client;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGALRM, &act, NULL);
	sigaction(SIGINT, &act, NULL);

	write(log_fd, "**Child process is initialized and ready to receive code\n", 57);
	printf("ppid %d\n", getppid());
    // Wait for input until server exits.

    while ( should_continue )
	{
		if (char_ready)
		{
			// Read newest char and write to output if line is complete.
			if ( (text[text_i++] = readCharOfMorse()) == '\n' )
			{
				int res = write(ofd, text, text_i);
				if ( res == -1 )
					write(log_fd, "**Write failed\n", 15);
				else if ( res == 0 )
				{
					perror("eof\n");
					break;
				}
				else
					write(log_fd, "**Wrote a line to output\n", 25);
				text_i = 0;
			}
		}
	}
	write(log_fd, "**EOF received in client, exiting\n", 34);

    close(ofd);
    close(log_fd);
    return(0);
}

// Move to morse.c ---------------------
char readCharOfMorse(void)
{
	if (char_index > 64)
		perror("Too long morse");
	char res = letter[char_index];
	char_ready = 0;
	char_index = 1;
	return(res);
}

// Handle signals sent by parent to child
void sighandler_client(int sig)
{
	switch(sig)
	{
		case SIGALRM:
			char_ready = 1;
			break;
		case SIGUSR1:
			char_index = char_index*2;
			break;
		case SIGUSR2:
			char_index = char_index*2+1;
			break;
		case SIGINT:
			should_continue = 0;
			break;
	}	
}
