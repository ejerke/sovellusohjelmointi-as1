/**
 * Mockup transfer between processes.
 */
#include "header.h"

int main(int argc,char **argv) {
    int ifd, ofd;

    // Quick and dirty command line parsing
    if (argc == 2) { // Only input file, output stdout
        ofd = STDOUT_FILENO;
        if (strcmp(argv[1],"-") == 0) {
            ifd = STDIN_FILENO;
        } else {
            ifd = open(argv[1],O_RDONLY);
            if (ifd < 0) {
                fprintf(stderr,"Opening input file failed\n");
                return -1;
            }
        }
    } else if (argc == 3) { // Both input and output file given
        if (strcmp(argv[1],"-") == 0) {
            ifd = STDIN_FILENO;
        } else {
            ifd = open(argv[1],O_RDONLY);
            if (ifd < 0) {
                fprintf(stderr,"Opening input file failed\n");
                return -1;
            }
        }
        if (strcmp(argv[2],"-") == 0) {
            ofd = STDOUT_FILENO;
        } else {
            ofd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
            if (ofd < 0) {
                fprintf(stderr,"Creating output file failed\n");
                return -1;
            }
        }
    } else {
        fprintf(stderr,"Usage: %s [input|-] [output|-]\n",argv[0]);
        return -1;
    }
    // pause()
    // sigset_t
    // sigaction()
    // sig(timed)wait()
    // async-signal-safe functions


    // Divide the program into two processes,
    // exec to run appropriate subprocess(server/client).
    pid_t  child_pid = 0;
    child_pid = fork();

    if (child_pid == 0)
    {

        char* client_exec = "./client";
        char* client_args[] = {"", NULL};
        printf("childi lähtee ny\n");

        execv(client_exec, client_args);
    }
    else if ( child_pid != -1 ) 
    {
        // Prepare the parameters for exec
        char* server_exec = "./server";

        char cpid_str[16];
        snprintf(cpid_str, sizeof(cpid_str), "%d", child_pid);

        char ifd_str[16];
        char ofd_str[16];

        snprintf(ifd_str, sizeof(ifd_str), "%d", ifd);
        snprintf(ofd_str, sizeof(ofd_str), "%d", ofd);
        

        char* server_args[] = {cpid_str, ifd_str, ofd_str, NULL};

        printf("parentti lähtee ny\n");

        execv(server_exec, server_args);
    }
    else
        printf("error in forking\n");

    return 0;
}
