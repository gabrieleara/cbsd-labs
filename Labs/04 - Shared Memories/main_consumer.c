#include <stdio.h>  // printf
#include <stdlib.h> // exit

#include "shmlib.h"

int main(int argc, char *argv[])
{
    struct shared_memory *shmem = shmem_get("keyfile", 'A');
    int err;

    if (shmem == NULL)
    {
        printf("Error retrieving shared memory!\r\n");
        return EXIT_FAILURE;
    }

    char c;
    int count = 0;

    while (shmem_get_data(shmem, &c))
    {
        printf("%02x\t", c);
        ++count;
        if(count == 8)
        {
            printf("\r\n");
            count = 0;
        }
    }

    printf("\r\n");

    err = shmem_unget(shmem);

    if (err)
    {
        printf("Error ungetting the shared memory!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
