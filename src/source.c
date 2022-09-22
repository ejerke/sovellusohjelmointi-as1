#include "header.h"

void Printer(){
	printf("source.c toimii\n");
}

void  ChildProcess(void)
{
    int   i;
	signal(SIGINT, sighandler);
	signal(SIGKILL, sighandler);

	delay(1000);

    for (i = 1; i <= MAX_COUNT; i++)
	{
		delay(10);
		sleep(20);
        printf("   This line is from child, value = %d\n", i);
	}
    printf("   *** Child process is done ***\n");
}

void  ParentProcess(pid_t child_pid)
{
    int   i;

	printf("childs id %d\n", child_pid);
	delay(1001);
	kill(SIGINT, child_pid);

    for (i = 1; i <= MAX_COUNT; i++)
	{
		delay(10);
        printf("This line is from parent, value = %d\n", i);
	}
    printf("*** Parent is done ***\n");
	kill(SIGKILL, child_pid);
}

void sighandler(int sig)
{
	switch(sig)
	{
		case SIGINT:
		case SIGKILL:
			printf("\n\nsus\n\n");
			if ( sig == SIGKILL )
				exit(0);
	}
		
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
