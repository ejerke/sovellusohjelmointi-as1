#include "header.h"


static volatile int char_index = 1;
static volatile int char_ready = 0;
static volatile int should_continue = 1;

int main(int argc, char **argv)
{
	char log_str[LOG_LINE_LENGTH];
	int ofd;
	int log_fd;

	// Start gives output file to client either as NULL (stdout) or a filename.
	log_fd = strtol(argv[1], NULL, 10);
	if ( log_fd < 0 )
	{
        perror("ei näin\n");
		kill(getppid(), SIGINT);
        return(-1);
    }
	write(log_fd, "**Client has access to log file\n", 32);


	// Start gives output file to client either as dash (stdout) or a filename.
	ofd = STDOUT_FILENO;
	if ( strcmp(argv[0],"-") )
		ofd = creat(argv[0], O_WRONLY);

	if ( ofd < 0 )
	{
        write(log_fd, "Bad output file descriptor in client, exiting\n", 46);
		kill(getppid(), SIGINT);
        return(-1);
    }

	sprintf(log_str, "**Client opened output stream based on: '%s'\n", argv[0]);
	write(log_fd, log_str, strlen(log_str));

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

	// Signal server that client is ready.
	kill(getppid(), SIGCHLD);
    // Wait for input until server exits.
    while ( should_continue )
	{
		pause();
		if (char_ready)
		{
			// Read newest char and write to output.
			char to_write = readCharOfMorse(&char_index, &char_ready);

			int res = write(ofd, &to_write, 1);
			if ( res == -1 )
				write(log_fd, "**Write failed\n", 15);
			else if ( res == 0 )
				break;
			// else
				// write(log_fd, "**Wrote a char to output\n", 25);
		}
	}
	write(log_fd, "**EOF received in client, exiting\n", 34);

    close(ofd);
    close(log_fd);
	kill(getppid(), SIGINT);
    return(0);
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
	kill(getppid(), SIGCHLD);
}
