#include "my_assert.h"

#include <stdlib.h>     // exit
#include <stdio.h>      // printf, remove
#include <sys/types.h>  // fork, mkfifo
#include <sys/stat.h>   // mkfifo, open
#include <sys/wait.h>   // wait
#include <fcntl.h>      // open

#include <unistd.h>     // fork, read, write, exec

#include <errno.h>      // errno
#include <stdbool.h>    // true, false

#define BUF_DIM     1024

#define N 4

int buffer[BUF_DIM];

#define FIFO_NAME "myfifo.fifo"
#define FIFO_PERM 0666

void producer()
{
    int base;
    int how_many_wrote;
    int returned_value;

    int fifofd;

    printf("Attempting to open the FIFO...\r\n");

    fifofd = open(FIFO_NAME, O_WRONLY);

    assert_perror(errno);

    printf("FIFO opened successfully!\r\n");

    for (int j = 0; j < N; ++j)
    {
        base = j * BUF_DIM;

        for (int i = 0; i < BUF_DIM; ++i)
        {
            buffer[i] = base + i;
        }

        printf("SENDING!\r\n");

        how_many_wrote = 0;

        do
        {
            returned_value = write(fifofd,
                                   ((unsigned char *)buffer) + how_many_wrote,
                                   sizeof(int) * BUF_DIM - how_many_wrote);

            printf("SENT!\r\n");

            // If it fails, it sets correctly errno
            assert_perror(errno);

            how_many_wrote += returned_value;
        } while (how_many_wrote < BUF_DIM * sizeof(int));
    }

    close(fifofd);
}

int main(int argc, char *argv[])
{
    pid_t pid;  // Returned by the fork command
    int status; // Used to wait child termination in father process

    // First we create the fifo
    mkfifo(FIFO_NAME, FIFO_PERM);

    assert_perror(errno);

    printf("Fifo created!\r\n");

    // Then we start the child process and give it a new source using exec
    pid = fork();

    assert_perror(errno);

    if (pid > 0)
    {
        // Father, do nothing we need to keep going.
        printf("Forked successfully!\r\n");
    }
    else if (pid == 0)
    {
        // Son, we need to start it with an exec
        printf("Attempting exec to start child code...\r\n");

        execl("./main_fifo_consumer.exe", "main_fifo_consumer.exe", (char*) NULL);

        assert_perror(errno);

        assert(false);
        return EXIT_FAILURE;
    }
    else
    {
        printf("ERROR!\r\n");
        assert(false);
        return  EXIT_FAILURE;
    }

    // Execute main code
    producer();

    printf("Waiting for the child...\r\n");

    // Then we wait for the child to terminate
    wait(&status);

    printf("Attempting to delete the FIFO...\r\n");

    // And we delete the FIFO once again
    remove(FIFO_NAME);

    printf("FIFO deleted...\r\n");

    return EXIT_SUCCESS;
}
