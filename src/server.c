#include "header.h"

void ParentProcess(pid_t child_pid, int ifd, int ofd)
{
    int   i;

	printf("childs id %d\n", child_pid);
	delay(1);
	kill(SIGINT, child_pid);

    // Allocate buffer
    char *buf = malloc(BLOCKSIZE);
    if (buf == NULL) return;
    while (1) {
        int s;
        s = read(ifd,buf,BLOCKSIZE);
        if (s < 0) return;
        if (s == 0) break; // input closed
        int r = 0;
		
		// SEND SIGNAL TO CHILD
		if (buf[0] == '1') kill(child_pid, SIGUSR1);
		if (buf[0] == '2') kill(child_pid, SIGUSR2);
		if (buf[0] == 'k') kill(child_pid, SIGTERM);
		if (buf[0] == 'p') kill(child_pid, SIGCONT);

		// continue normally
        while (r < s) {
            int t = write(ofd,buf+r,s-r);
            if (t < 0) {
                return;
            }
            r += t;
        }
    }
    free(buf);
    close(ifd);
    close(ofd);

    printf("*** Parent is done ***\n");
	kill(child_pid, SIGTERM);
}
