#include "delay.h"

void delay_micro(unsigned int t)
{ 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is achieved
    while ( clock() < start_time + t )
        ;
}
