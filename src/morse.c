#include "header.h"
#include <assert.h>

/**
 * 
 * Functions needed to convert between characters
 * of text, morse code, and signal.
 * 
 * morse '.' corrseponds to signal SIGUSR1
 * morse '-' corrseponds to signal SIGUSR2
 * 
 * The rest of the morse (mainly the gaps)
 * are implemented with signal SIGALRM
 * 
 * 1x means space between characters
 * 2x means space between words
 * 3x means space between sentences (a dot)
 * 4x ??
 * 
 * 
 * 8x means an error (mostly from client to server) ??
 * 
 * 
*/


char* morseEncode(char x)
{
    // Return morse based on char
    switch (x) {
    case 'a':
        return ".-";
    case 'b':
        return "-...";
    case 'c':
        return "-.-.";
    case 'd':
        return "-..";
    case 'e':
        return ".";
    case 'f':
        return "..-.";
    case 'g':
        return "--.";
    case 'h':
        return "....";
    case 'i':
        return "..";
    case 'j':
        return ".---";
    case 'k':
        return "-.-";
    case 'l':
        return ".-..";
    case 'm':
        return "--";
    case 'n':
        return "-.";
    case 'o':
        return "---";
    case 'p':
        return ".--.";
    case 'q':
        return "--.-";
    case 'r':
        return ".-.";
    case 's':
        return "...";
    case 't':
        return "-";
    case 'u':
        return "..-";
    case 'v':
        return "...-";
    case 'w':
        return ".--";
    case 'x':
        return "-..-";
    case 'y':
        return "-.--";
    case 'z':
        return "--..";
    case '1':
        return ".----";
    case '2':
        return "..---";
    case '3':
        return "...--";
    case '4':
        return "....-";
    case '5':
        return ".....";
    case '6':
        return "-....";
    case '7':
        return "--...";
    case '8':
        return "---..";
    case '9':
        return "----.";
    case '0':
        return "-----";
    default:
        printf("Found invalid character\n");
        return(0);
    }
}

int sendCharInMorse(char a, pid_t target)
{
    // assert( a == '.' || a == '-' );

    char to_send[5];
    to_send[4] = 0;
    strcpy(to_send, morseEncode(a));
    int i = 0;

    while ( to_send[i] )
    {
    
        switch ( to_send[i] )
        {
        case '.':
            kill(target, SIGUSR1);
            break;
        
        case '-':
            kill(target, SIGUSR2);
            break;

        default:
            break;
        }
        i++;
        delay(100);

    }

    return(0);
}

