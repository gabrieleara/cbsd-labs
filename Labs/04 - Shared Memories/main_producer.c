#include "myassert.h"   // assert_perror

#include <stdio.h>      // printf
#include <stdlib.h>     // exit

#include <errno.h>      // errno

#include <sys/ipc.h>    // shmget, shmctl
#include <sys/shm.h>    // shmget, shmctl, shmat, shmdt

#include <signal.h>     // signal

#include <stdbool.h>    // bool

#include "shmlib.h"









bool terminate = false;

void sigint_handler(int signum)
{
    terminate = true;
}

int main(int argc, char* argv[])
{
    int shmkey;
    int shmid;
    void* shared_ptr;
    int value;

    // Using a special file to create a (possibly) unique key for the shared
    // memory
    shmkey = ftok("keyfile", 'A');
    assert_perror(errno);

    printf("The shared memory key is %d.\r\n", shmkey);

    // Create the shared memory object (forcing its creation, otherwise error)
    shmid = shmget(shmkey, sizeof(int), 0666 | IPC_CREAT | IPC_EXCL);
    assert_perror(errno);

    // Attaching the shared memory to the given variable
    shared_ptr = shmat(shmid, NULL, 0);
    assert_perror(errno);

    // Requesting a value from command line
    printf("Please, insert an integer value: ");
    // flush(stdout);

    scanf("%d", &value);

    // Writing to shared memory (without using protection)
    *((int*) shared_ptr) = value;

    // We will wait for user input to destroy the shared memory
    printf("Execute a ^C to terminate the program correctly...");
    fflush(stdout);

    // The easy way to use a signal handler is this, but it's sometimes
    // considered unsafe
    signal(SIGINT, sigint_handler);

    // The hard way is the following one
    // TODO

    while(!terminate)
        ;

    printf("\r\n");

    // Detaching the shared variable (not necessary if we destroy the shared
    // memory location)
    // shmdt(shared_ptr);
    // assert_perror(errno);

    shmctl(shmid, IPC_RMID, NULL);
    assert_perror(errno);

    return EXIT_SUCCESS;
}
