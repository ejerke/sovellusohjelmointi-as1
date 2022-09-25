#include "header.h"

static int signal_array[5] = {
	SIGINT,
	SIGTERM,
	SIGCONT,
	SIGUSR1,
	SIGUSR2,
};

void  ChildProcess(void)
{
    int   i;
	int   s = 0;

	// Start listening to signals listed in signal_array
	while (s++ < sizeof(signal_array))
		signal(signal_array[s], sighandler_client);

	delay(1000);

    for (i = 1; i <= MAX_COUNT; i++)
	{
        printf("   This line is from child, value = %d\n", i);
		delay(20000);
	}
	delay(30000);
    printf("   *** Child process is done ***\n");
}

// Handle signals sent by parent to child
void sighandler_client(int sig)
{
	printf("\n\nIN SIG HANDLER\n\n");
	switch(sig)
	{
		case SIGCONT:
			printf("\n\nCONTINUE\n\n");
			break;
		case SIGUSR1:
			printf(" -> 1 registered\n");
			break;
		case SIGUSR2:
			printf(" -> 2 registered\n");
			break;
		//KILL
		case SIGINT:
		case SIGTERM:
			exit(0);
	}
		
}