#include <stdlib.h>
#include <stdio.h>

#include "my_library.h"

extern void my_fun();

/*
 * Either the attribute is placed before the function definition or after the
 * function declaration.
 */

__attribute__((deprecated)) void deprecated()
{
    static int count = 0;
    ++count;
    errprintf("Deprecated function was called %d times!\r\n", count);
}

__attribute__((nonnull(1))) void print_address(int *addr)
{
    printf("Address of the given integer: %lx.\r\n", (unsigned long int) addr);
}

__attribute__((noreturn)) void exit_function()
{
    errprintf("Program will now terminate...\r\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    int var = 0;

    printf("Hello World!\r\n");

    my_fun();

    /* deprecated(); */
    /* print_address(NULL); */

    print_address(&var);

    exit_function(EXIT_SUCCESS);
}
