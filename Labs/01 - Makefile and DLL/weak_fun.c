#include <stdio.h>

void my_fun() __attribute__((weak));

void my_fun()
{
    printf("Weak function was called!\r\n");
}
