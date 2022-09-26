#include "header.h"

int main(int argc, char **argv)
{
    int child_pid, ifd, ofd;
    if ( argc < 3 )
        return(-1);
    child_pid = strtol(argv[0], NULL, 10);
    ifd =       strtol(argv[1], NULL, 10);
    ofd =       strtol(argv[2], NULL, 10);

    // Allocate buffer
    char *buf = malloc(BLOCKSIZE);
    if (buf == NULL) return(0);
    while (1) {
        int s;
        s = read(ifd,buf,BLOCKSIZE);
        if (s < 0) return(0);
        if (s == 0) break; // input closed
        int r = 0;
		
		// SEND SIGNAL TO CHILD
		if (buf[0] == '1') kill(child_pid, SIGUSR1);
		if (buf[0] == '2') kill(child_pid, SIGUSR2);
		if (buf[0] == '3') kill(child_pid, SIGALRM);

		// continue normally
        while (r < s) {
            int t = write(ofd,buf+r,s-r);
            if (t < 0) {
                return(0);
            }
            r += t;
        }
    }
    free(buf);
    close(ifd);
    close(ofd);

	kill(child_pid, SIGTERM);
}

// int ParentProcess(pid_t child_pid, int ifd, int ofd)
// {
// 	printf("childs id is now %d\n", child_pid);
// 	delay(1);
// 	kill(SIGINT, child_pid);

//     // Allocate buffer
//     char *buf = malloc(BLOCKSIZE);
//     if (buf == NULL) return(0);
//     while (1) {
//         int s;
//         s = read(ifd,buf,BLOCKSIZE);
//         if (s < 0) return(0);
//         if (s == 0) break; // input closed
//         int r = 0;
		
// 		// SEND SIGNAL TO CHILD
// 		if (buf[0] == '1') kill(child_pid, SIGUSR1);
// 		if (buf[0] == '2') kill(child_pid, SIGUSR2);
// 		if (buf[0] == 'k') kill(child_pid, SIGTERM);
// 		if (buf[0] == 'p') kill(child_pid, SIGCONT);

// 		// continue normally
//         while (r < s) {
//             int t = write(ofd,buf+r,s-r);
//             if (t < 0) {
//                 return(0);
//             }
//             r += t;
//         }
//     }
//     free(buf);
//     close(ifd);
//     close(ofd);

//     printf("*** Parent is done ***\n");
// 	kill(child_pid, SIGTERM);
// }
