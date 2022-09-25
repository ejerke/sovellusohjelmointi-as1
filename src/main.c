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

    pid_t  child_pid;

    // Divide the program into two processes,
    // exec to run appropriate subprocess.

    // char* server = "./server";

     child_pid = fork();
     if (child_pid == 0) 
        ChildProcess();
     else 
        ParentProcess(child_pid, ifd, ofd);

    return 0;
}
