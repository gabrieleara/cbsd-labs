#include "my_assert.h"

#include <stdio.h>      // printf
#include <sys/types.h>  // fork
#include <sys/wait.h>   // wait
#include <unistd.h>     // pipe, fork, read, write

#include <errno.h>      // errno
#include <stdbool.h>    // true, false

#define PIPE_READ   0
#define PIPE_WRITE  1

#define BUF_DIM     1024

#define N 4

int buffer[BUF_DIM];

void producer(int pipefd[])
{
    int base;
    int how_many_wrote;
    int returned_value;

    close(pipefd[PIPE_READ]);

    for(int j = 0; j < N; ++j)
    {
        base = j * BUF_DIM;

        for(int i = 0; i < BUF_DIM; ++i)
        {
            buffer[i] = base + i;
        }

        printf("SENDING!\r\n");

        how_many_wrote = 0;

            do
        {
            returned_value = write(pipefd[PIPE_WRITE],
                                   ((unsigned char *)buffer) + how_many_wrote,
                                   sizeof(int) * BUF_DIM - how_many_wrote);

            printf("SENT!\r\n");

            // If it fails, it sets correctly errno
            assert_perror(errno);

            how_many_wrote += returned_value;
        } while(how_many_wrote < BUF_DIM * sizeof(int));
    }

    close(pipefd[PIPE_WRITE]);
}

void consumer(int pipefd[])
{
    int how_many;
    int global_count = 0;
    int num_read;

    close(pipefd[PIPE_WRITE]);

    do
    {
        how_many = num_read =
            read(pipefd[PIPE_READ], buffer, sizeof(int) * BUF_DIM);

        //printf("A) Read %d bytes!\r\n", num_read);

        while(how_many < BUF_DIM * sizeof(int) && num_read != 0)
        {
            assert_perror(errno);

            num_read = read(pipefd[PIPE_READ],
                    (unsigned char*) buffer + how_many,
                    sizeof(int) * BUF_DIM - how_many
                );

            //printf("B) Read %d bytes!\r\n", num_read);

            how_many += num_read;
        }

        if(num_read == 0)
            return;

        assert_perror(errno);

        for(int i = 0; i < BUF_DIM; ++i)
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
    } while(num_read);

    printf("\r\n");
}




int main(int argc, char *argv[])
{
    int pipefd[2];  // Contains the two ends of the pipe
    //int error;      // Used to check for errors in standard library calls

    pid_t pid;      // Returned by the fork command
    int status;     // Used to wait child termination in father process

    /* error = */pipe(pipefd);

    assert_perror(errno);

    pid = fork();

    assert_perror(errno);

    if (pid > 0)
    {
        // Father
        printf("FATHER!\r\n");
        producer(pipefd);

        wait(&status);

    } else if (pid == 0)
    {
        // Son

        printf("SON!\r\n");
        consumer(pipefd);
    } else {
        printf("ERROR!\r\n");
        assert(false);
    }

    return 0;
}
