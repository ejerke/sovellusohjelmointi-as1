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
    case 'A':
        return ".-";
    case 'b':
    case 'B':
        return "-...";
    case 'c':
    case 'C':
        return "-.-.";
    case 'd':
    case 'D':
        return "-..";
    case 'e':
    case 'E':
        return ".";
    case 'f':
    case 'F':
        return "..-.";
    case 'g':
    case 'G':
        return "--.";
    case 'h':
    case 'H':
        return "....";
    case 'i':
    case 'I':
        return "..";
    case 'j':
    case 'J':
        return ".---";
    case 'k':
    case 'K':
        return "-.-";
    case 'l':
    case 'L':
        return ".-..";
    case 'm':
    case 'M':
        return "--";
    case 'n':
    case 'N':
        return "-.";
    case 'o':
    case 'O':
        return "---";
    case 'p':
    case 'P':
        return ".--.";
    case 'q':
    case 'Q':
        return "--.-";
    case 'r':
    case 'R':
        return ".-.";
    case 's':
    case 'S':
        return "...";
    case 't':
    case 'T':
        return "-";
    case 'u':
    case 'U':
        return "..-";
    case 'v':
    case 'V':
        return "...-";
    case 'w':
    case 'W':
        return ".--";
    case 'x':
    case 'X':
        return "-..-";
    case 'y':
    case 'Y':
        return "-.--";
    case 'z':
    case 'Z':
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

    // User defined characters, also need to be implemented
    // separately to client-side.

    // every encoded '_' means one sent SIG_ALRM, also the function
    // sendCharOfMorse always adds one SIG_ALRM to the end of a char
    case ' ': 
        return "_";
    case '.':
        return "__";
    case ',':
        return "___";
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

        case '_':
            kill(target, SIGALRM);
            break;

        default:
            break;
        }
        i++;
        delay_micro(DEFAULT_KILL_DELAY);

    }
    kill(target, SIGALRM); // Send always at least character end.
    delay_micro(END_KILL_DELAY);
    return(0);
}

