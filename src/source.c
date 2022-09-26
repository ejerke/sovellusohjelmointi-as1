#include "header.h"

void delay_micro(int micro_seconds)
{ 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is achieved
    while (clock() < start_time + micro_seconds)
        ;
}
