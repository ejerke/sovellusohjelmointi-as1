#include "header.h"

static volatile int should_continue = 1;

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

    // Read commandline arguments to numbers.
    int child_pid, ifd, log_fd;
    child_pid = strtol(argv[0], NULL, 10);
    ifd =       strtol(argv[1], NULL, 10);
    log_fd =    strtol(argv[2], NULL, 10);

	write(log_fd, "Server is ready to start sending morse\n", 39);

    delay_micro(10000);

    // Allocate buffer
    char *buf = malloc(BLOCKSIZE);
    if (buf == NULL) return(0);
    while ( should_continue )
    {
        int read_size;
        read_size = read(ifd,buf,BLOCKSIZE);
        if (read_size < 0) write(log_fd, "Something went wrong with read\n", 31);
        if (read_size == 0) break;

		// Send buffer char by char to client.
        int i = 0;
        while ( i < read_size && buf[i] != EOF )
        {
            printf(" loppu   '%c'\n", buf[i]);
            sendCharInMorse(buf[i], child_pid, log_fd);
            i++;
        }
    }

	kill(child_pid, SIGINT);

	write(log_fd, "EOF reached in server, exiting\n", 31);
    free(buf);
    close(ifd);
}

// Handles only SIGINT for server.
void sighandler_server(int sig)
{
    should_continue = 0;
}