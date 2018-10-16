#include "my_assert.h"

#include <stdlib.h>    // exit
#include <stdio.h>     // printf
#include <sys/stat.h>  // open
#include <fcntl.h>     // open

#include <unistd.h> // read, write

#include <errno.h>   // errno
#include <stdbool.h> // true, false

#define BUF_DIM 1024

int buffer[BUF_DIM];

#define FIFO_NAME "myfifo.fifo"

void consumer()
{
    int how_many;
    int global_count = 0;
    int num_read;

    int fifofd;

    fifofd = open(FIFO_NAME, O_RDONLY);

    do
    {
        how_many = num_read =
            read(fifofd, buffer, sizeof(int) * BUF_DIM);

        //printf("A) Read %d bytes!\r\n", num_read);

        while (how_many < BUF_DIM * sizeof(int) && num_read != 0)
        {
            assert_perror(errno);

            num_read = read(fifofd,
                            (unsigned char *)buffer + how_many,
                            sizeof(int) * BUF_DIM - how_many);

            //printf("B) Read %d bytes!\r\n", num_read);

            how_many += num_read;
        }

        if (num_read == 0)
            return;

        assert_perror(errno);

        for (int i = 0; i < BUF_DIM; ++i)
        {
            printf("%#06x", buffer[i]);

            ++global_count;

            if (global_count == 4)
            {
                global_count = 0;
                printf("\r\n");
            }
            else
            {
                printf("\t");
            }
        }
    } while (num_read);

    printf("\r\n");

    close(fifofd);
}

int main(int argc, char *argv[])
{
    printf("Child code started successfully!");

    consumer();

    return EXIT_SUCCESS;
}
