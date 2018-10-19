#include "myassert.h"   // assert_perror

#include <stdio.h>      // printf
#include <stdlib.h>     // exit

#include <errno.h>      // errno

#include <sys/ipc.h>    // shmget, shmctl
#include <sys/shm.h>    // shmget, shmctl, shmat, shmdt

#include <signal.h>     // signal

#include <stdbool.h>    // bool

int main(int argc, char *argv[])
{
    int shmkey;
    int shmid;
    void *shared_ptr;
    int value;

    // Using a special file to create a (possibly) unique key for the shared
    // memory
    shmkey = ftok("keyfile", 'A');
    assert_perror(errno);

    printf("The shared memory key is %d.\r\n", shmkey);

    // Get a previously created shared memory object
    shmid = shmget(shmkey, sizeof(int), 0666);
    assert_perror(errno);

    // Attaching the shared memory to the given variable
    shared_ptr = shmat(shmid, NULL, 0);
    assert_perror(errno);

    // Copying the value within the shared memory into a local variable (without
    // using protection)
    value = *((int*) shared_ptr);

    // Detaching the shared variable
    shmdt(shared_ptr);
    assert_perror(errno);

    // Printing the result
    printf("The value within the shared memory is %d.\r\n", value);

    return EXIT_SUCCESS;
}
