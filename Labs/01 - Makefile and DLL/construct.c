#include <stdio.h>

void constructor() __attribute__((constructor,weak));
void destructor() __attribute__((destructor,weak));

void constructor()
{
    printf("Constructor function was called!\r\n");
}

void destructor()
{
    printf("Destructor function was called!\r\n");
}
