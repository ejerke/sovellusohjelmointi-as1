#include "header.h"

// static int signal_array[3] = {
// 	// SIGINT,
// 	// SIGTERM,
// 	SIGALRM,
// 	SIGUSR1,
// 	SIGUSR2,
// };
static char text[BLOCKSIZE];
static int text_i;

static const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??54$3?? 2.,+-_??16=/?????7???8\n90";

static volatile int char_index = 1;
static volatile int char_ready = 0;

int main(int argc, char **argv)
{
	// pid_t parent_id = getppid();
	memset(text, 0, sizeof(text));

    int ofd = strtol(argv[2], NULL, 10);

	// Start listening to signals listed in signal_array
    // exec to run appropriate subprocess(server/client).
	struct sigaction act;
	act.sa_handler = &sighandler_client;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGALRM, &act, NULL);

    printf("   *** Child process is ready ***\n");

    // Wait for more input until server exits.
    while (1)
	{
		if (char_ready)
		{
			text[text_i] = readCharOfMorse();

			if ( text[text_i] == '\n')
			{
				// printf("received a complete line, text now:\n");
				// printf("%s\n", text);
				if ( write(ofd, text, BLOCKSIZE) == -1 )
					printf("didnt write\n");
			}
			text_i++;
		}
	}

    close(ofd);
    return(0);
}

// Move to morse.c
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
	}	
}