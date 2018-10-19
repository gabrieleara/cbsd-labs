#include <limits.h>     // max char

#include <stdio.h>      // printf
#include <stdlib.h>     // exit

#include "shmlib.h"

int main(int argc, char* argv[])
{
    struct shared_memory* shmem = shmem_create("keyfile", 'A');
    int err;

    if (shmem == NULL)
    {
        printf("Error in shared memory initialization!\r\n");
        return EXIT_FAILURE;
    }

    for (char c = 0; c < SCHAR_MAX; ++c)
    {
        shmem_put_data(shmem, c);
        printf("%02x\t", c);

        if (c % 8 == 7)
            printf("\r\n");
    }

    shmem_put_data(shmem, SCHAR_MAX);
    printf("%02x\t", SCHAR_MAX);

    printf("\r\n\r\n");

    shmem_end_comm(shmem);

    err = shmem_destroy(shmem);

    if (err)
    {
        printf("Error destroying the shared memory!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
