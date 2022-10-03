#include "header.h"

// static int signal_array[3] = {
// 	// SIGINT,
// 	// SIGTERM,
// 	SIGALRM,
// 	SIGUSR1,
// 	SIGUSR2,
// };
static char text[1024];
static int text_i;

static const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??54$3?? 2.,+-_??16=/?????7???8?90";


static volatile int char_index = 1;
static volatile int char_ready = 0;

int main()
{
	// pid_t parent_id = getppid();
	memset(text, 0, sizeof(text));
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
	// int   s = 0;
	// while (s++ < sizeof(signal_array))
	// 	signal(signal_array[s], sighandler_client);

    // Wait for more input until server exits.
    while (1)
		if (char_ready)
		{
			text[text_i] = readCharOfMorse();
			if ( text[text_i] == '_')
				printf("total:%s\n", text);
			text_i++;
		}


    // printf("   *** Child process is done ***\n");
    return(0);
}

char readCharOfMorse(void)
{
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