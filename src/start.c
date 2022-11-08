/**
 * Mockup transfer between processes.
 */
#include "header.h"

int main(int argc,char **argv) {
    
    // Only check that argument count seems valid and open log, server and client will handle the args.
    if ( argc < 2 || argc > 4 ) {
        fprintf(stderr, "Usage: %s [input|-] [output|-] [log-file|-]\n", argv[0]);
        return(-1);
    }

    int log_fd;
    if ( argc == 4 && strcmp(argv[3], "-") )
        log_fd = creat(argv[3], O_WRONLY);
    else
        log_fd = creat(DEFAULT_LOG, O_WRONLY);
    
    write(log_fd, "Log file opened by start\n", 25);
    char log[16];
    snprintf(log, sizeof(log), "%d", log_fd);

    pid_t  child_pid = 0;
    child_pid = fork();

    if ( child_pid == 0 ) // In Client
    {
        // Name the executable
        char client_exec[] = "./client";

        //                     ifd   log
        char* client_args[] = {NULL, NULL, NULL};

        // log
        client_args[1] = log;

        // ifd
        if ( argv[2] )
            client_args[0] = argv[2];
        else
            client_args[0] = "-";

        execv(client_exec, client_args);
    }
    else if ( child_pid != -1 ) // In Server
    {
        // Prepare the parameters for exec
        char server_exec[] = "./server";
        char cpid_str[16];
        snprintf(cpid_str, sizeof(cpid_str), "%d", child_pid);

        //                    child_pid  ifd  log
        char* server_args[] = {cpid_str, "-", log, NULL};

        // ifd
        if ( strcmp(argv[1],"-") )
            server_args[1] = argv[1];


        execv(server_exec, server_args);
    }
    else
       perror("error in forking\n");

    return(0);
}
