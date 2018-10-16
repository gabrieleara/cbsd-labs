#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

// #include "my_library.h"

void* dlhandle_ptr;

void (*errprintf)(const char *my_format, ...);

extern void my_fun();

/*
 * Either the attribute is placed before the function definition or after the
 * function declaration.
 */

__attribute__((deprecated)) void deprecated()
{
    static int count = 0;
    ++count;
    (*errprintf)("Deprecated function was called %d times!\r\n", count);
}

__attribute__((nonnull(1))) void print_address(int *addr)
{
    printf("Address of the given integer: %lx.\r\n", (unsigned long int) addr);
}

__attribute__((noreturn)) void exit_function()
{
    (*errprintf)("Program will now terminate...\r\n");

    dlclose(dlhandle_ptr);

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    int var = 0;
    char* error;

    printf("Hello World!\r\n");

    my_fun();

    if (argc < 2)
    {
        fprintf(stderr, "Must supply dynamic library location!\r\n");
        exit(EXIT_FAILURE);
    }

    /* See also man dlopen for other flags that may be used in this case. */
    dlhandle_ptr = dlopen(argv[1], RTLD_LAZY);

    if (!dlhandle_ptr)
    {
        fprintf(stderr, "%s\r\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); /* Clear any previously existing error. */

    *(void **)(&errprintf) = dlsym(dlhandle_ptr, "errprintf");

    /*
     * dlsym may return NULL, the only way to check for an error is to use
     * dlerror after it has been cleared.
     */
    error = dlerror();

    if (error != NULL)
    {
        fprintf(stderr, "%s\r\n", dlerror());
        exit(EXIT_FAILURE);
    }

    /* NOTICE: all samples now use function pointers and not function names */

    /* deprecated(); */
    /* print_address(NULL); */

    print_address(&var);

    exit_function(EXIT_SUCCESS);
}
