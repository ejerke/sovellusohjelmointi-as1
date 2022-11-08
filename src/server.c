#include "header.h"

static volatile int should_continue = 1;
// static volatile int child_ready = 0;

int main(int argc, char **argv)
{
    if ( argc < 3 )
        return(-1);

    // Start listening to signals

	struct sigaction act;
	act.sa_handler = &sighandler_server;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGCHLD, &act, NULL); /* Child uses to indicate wanting more time */
	sigaction(SIGALRM, &act, NULL); /* Child uses to indicate being ready */

    // Read commandline arguments to numbers.
    int child_pid, ifd, log_fd;
    child_pid = strtol(argv[0], NULL, 10);

    // Read log file descriptor.
	log_fd = strtol(argv[2], NULL, 10);
    if ( log_fd < 0 )
    {
        perror("ei näin\n");
        kill(child_pid, SIGINT);
        wait(NULL);
        return(-1);
    }
	write(log_fd, "Server has access to log file\n", 30);


    // Open ifd and check for errors.
    ifd = STDIN_FILENO;
    if ( strcmp(argv[1],"-") )
        ifd = open(argv[1], O_RDONLY);

    if ( child_pid == 0 || ifd < 0 )
    {
        write(log_fd, "Server initialization failed, exiting\n", 38);
        kill(child_pid, SIGINT);
        wait(NULL);
        return(-1);
    }

    char log_str[LOG_LINE_LENGTH];
    sprintf(log_str, "Server opened input stream based on '%s'\n", argv[1]);
	write(log_fd, log_str, strlen(log_str));

    // Allocate buffer
    char *buf = malloc(BLOCKSIZE);
    if ( buf == NULL) return(0);
    int read_size;

    // Wait for child to get ready to receive input:
    // while ( !child_ready )
    //     ;
    // Wait a bit to make sure client is ready first.
    delay_micro(2000);
    while ( should_continue )
    {
        read_size = read(ifd,buf,BLOCKSIZE);
        if ( read_size < 0 )
            write(log_fd, "Interrupt in server, possibly SIGINT\n", 37);
        if ( read_size <= 0 ) break;

		// Send buffer char by char to client.
        int i = 0;

        while ( i < read_size && buf[i] != EOF && should_continue)
        {
            sendCharInMorse(buf[i], child_pid, log_fd);
            i++;
        }
    }

	write(log_fd, "EOF reached in server, exiting\n", 31);
    free(buf);
    close(ifd);
    delay_micro(1000);
	kill(child_pid, SIGINT);
    wait(NULL);
    return(0);
}

// SIGINT to exit cleanly and SIGCHLD to give client a bit more time (to write).
void sighandler_server(int sig)
{
    switch ( sig )
    {
    case SIGINT:
        should_continue = 0;
        break;
    case SIGCHLD:
        delay_micro(2000);
        break;
    }
}
