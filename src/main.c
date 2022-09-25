/**
 * Mockup for ELEC-C7310 assignment 1.
 * This only writes data directly without doing a data transfer between processes.
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


    // Divide the program into two processes,
    // exec to run appropriate subprocess.
    pid_t  child_pid = 0;
    child_pid = fork();
    printf("forkki tehty\n");

    if (child_pid == 0)
    {

    char* client_exec = "client";
    char* client_args[] = {""};
    printf("childi lähtee ny\n");

    execvp(client_exec, client_args);
    // ChildProcess();
    }
    else 
    {
    // Prepare the parameters for exec
    char* server_exec = "server";

    char cpid_str[16];
    snprintf(cpid_str, sizeof(cpid_str), "%d", child_pid);

    char ifd_str[16];
    char ofd_str[16];

    snprintf(ifd_str, sizeof(ifd_str), "%d", ifd);
    snprintf(ofd_str, sizeof(ofd_str), "%d", ofd);
    

    char* server_args[] = {cpid_str, ifd_str, ofd_str};

    printf("parentti lähtee ny\n");

    execvp(server_exec, server_args);
    // ParentProcess(child_pid, ifd, ofd);
    }

    return 0;
}
