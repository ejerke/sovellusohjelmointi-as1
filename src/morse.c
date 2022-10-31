#include "header.h"
#include <assert.h>
#include <string.h>
/**
 * 
 * Functions needed to convert between characters
 * of text, morse code, and signal.
 * 
 * morse '.' corrseponds to signal SIGUSR1
 * morse '-' corrseponds to signal SIGUSR2
 * 
 * SIGALRM means that the previously sent signals can be calculated.
 * 
 * The morse code is turned into an index of the letter array in client by incrementing
 * the index variable by *2 on SIGUSR1 ('.') and by *2+1 on SIGUSR2 ('-').
 * 
 */

// Constant list of letters to read based on index, calculated as stated above.
static const char *letter = "**etianmsurwdkgohvf?l?pjbxcyzq??54$3?? 2.,+-_??16=/?????7???8\n90";

char* morseEncode(char x, int log_fd)
{
    // Return morse based on char
    switch (x) {
    case 'a':
    case 'A':
        return(".-");
    case 'b':
    case 'B':
        return("-...");
    case 'c':
    case 'C':
        return("-.-.");
    case 'd':
    case 'D':
        return("-..");
    case 'e':
    case 'E':
        return(".");
    case 'f':
    case 'F':
        return("..-.");
    case 'g':
    case 'G':
        return("--.");
    case 'h':
    case 'H':
        return("....");
    case 'i':
    case 'I':
        return("..");
    case 'j':
    case 'J':
        return(".---");
    case 'k':
    case 'K':
        return("-.-");
    case 'l':
    case 'L':
        return(".-..");
    case 'm':
    case 'M':
        return("--");
    case 'n':
    case 'N':
        return("-.");
    case 'o':
    case 'O':
        return("---");
    case 'p':
    case 'P':
        return(".--.");
    case 'q':
    case 'Q':
        return("--.-");
    case 'r':
    case 'R':
        return(".-.");
    case 's':
    case 'S':
        return("...");
    case 't':
    case 'T':
        return("-");
    case 'u':
    case 'U':
        return("..-");
    case 'v':
    case 'V':
        return("...-");
    case 'w':
    case 'W':
        return(".--");
    case 'x':
    case 'X':
        return("-..-");
    case 'y':
    case 'Y':
        return("-.--");
    case 'z':
    case 'Z':
        return("--..");
    case '1':
        return(".----");
    case '2':
        return("..---");
    case '3':
        return("...--");
    case '4':
        return("....-");
    case '5':
        return(".....");
    case '6':
        return("-....");
    case '7':
        return("--...");
    case '8':
        return("---..");
    case '9':
        return("----.");
    case '0':
        return("-----");

    // User defined characters, also need to be implemented
    // separately to client-side (done by adding them to letter array static variable)

    case ' ': 
        return("..--.");
    case '=':
        return("-...-");
    case '+':
        return(".-.-.");
    case '-':
        return(".-.--");
    case '.':
        return(".-...");
    case ',':
        return(".-..-");
    case '_':
        return(".--..");
    case '\n':
        return("---.-");

    // Send an underscore for a character that is not implemented.
    default:
        // printf("---- CHAR: '%c' not implemented\n", x);
        write(log_fd, "Char not implemented\n", 21);
        return(".--..");
    }
}

int sendCharInMorse(char a, pid_t target, int log_fd)
{
    char to_send[7];
    memset(to_send, 0, 7);
    strcpy(to_send, morseEncode(a, log_fd));
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
        }
        delay_micro(DEFAULT_KILL_DELAY);
        i++;
    }
    kill(target, SIGALRM); // Send always at least character end.
    delay_micro(DEFAULT_KILL_DELAY);

    return(0);
}

// readCharOfMorse
char readCharOfMorse(volatile int* char_index, volatile int* char_ready)
{
    char a = 0;
	if (*char_index > 64)
        a = '_';
		// perror("Too long morse");
	char res;
    if (a)
        res = a;
    else
        res = letter[*char_index];

   *char_ready = 0;
   *char_index = 1;
   return(res);
}
