#include "header.h"

int main(int argc, char **argv)
{
    int child_pid, ifd;
    if ( argc < 2 )
        return(-1);

    child_pid = strtol(argv[0], NULL, 10);
    ifd =       strtol(argv[1], NULL, 10);
    
    delay_micro(10000);
    printf("**** Parent is ready ****\n");
    // Allocate buffer
    char *buf = malloc(BLOCKSIZE);
    if (buf == NULL) return(0);
    while (1) {
        int s;
        s = read(ifd,buf,BLOCKSIZE);
        if (s < 0) return(0);
        if (s == 0) break; // input closed
        int r = 0;
        
		// continue normally
        while ( r < s &&  buf[r] != EOF ) {
            sendCharInMorse(buf[r], child_pid);
            r++;
        }
    }
    free(buf);
    close(ifd);

	kill(child_pid, SIGTERM);
}
