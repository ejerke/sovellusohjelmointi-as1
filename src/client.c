#include "header.h"

// static int signal_array[3] = {
// 	// SIGINT,
// 	// SIGTERM,
// 	SIGALRM,
// 	SIGUSR1,
// 	SIGUSR2,
// };
static int received[1024];

int main()
{
	// pid_t parent_id = getppid();
	memset(received, 0, sizeof(received));
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
        ;

    printf("   *** Child process is done ***\n");
    return(0);
}

// Handle signals sent by parent to child
void sighandler_client(int sig)
{
	switch(sig)
	{
		case SIGALRM:
			printf(" -> space received\n");
			break;
		case SIGUSR1:
			printf(" -> short received\n");
			break;
		case SIGUSR2:
			printf(" -> long received\n");
			break;
	}	
}