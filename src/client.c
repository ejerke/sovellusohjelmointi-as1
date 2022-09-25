#include "header.h"

static int signal_array[3] = {
	// SIGINT,
	// SIGTERM,
	SIGALRM,
	SIGUSR1,
	SIGUSR2,
};

int main()
{
    int   i;
	int   s = 0;

	// Start listening to signals listed in signal_array
	while (s++ < sizeof(signal_array))
		signal(signal_array[s], sighandler_client);

    for (i = 1; i <= MAX_COUNT; i++)
	{
        printf("   from child, value = %d\n", i);
		delay(20);
	}

    // Wait for more input until server exits.
    while (1)
        ;

    printf("   *** Child process is done ***\n");
    return(0);
}

// int ChildProcess(void)
// {
//     int   i;
// 	int   s = 0;

// 	// Start listening to signals listed in signal_array
// 	while (s++ < sizeof(signal_array))
// 		signal(signal_array[s], sighandler_client);

// 	delay(1000);

//     for (i = 1; i <= MAX_COUNT; i++)
// 	{
//         printf("   This line is from child, value = %d\n", i);
// 		delay(20000);
// 	}
// 	delay(30000);
//     printf("   *** Child process is done ***\n");
//     return(0);
// }

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