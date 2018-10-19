#ifndef MYSHMLIB_H
#define MYSHMLIB_H

#include <stdbool.h>

struct shared_memory;

struct shared_memory* shmem_create(char* keyfile, char proj_id);
int shmem_destroy(struct shared_memory* shmem_ptr);

struct shared_memory *shmem_get(char *keyfile, char proj_id);
int shmem_unget(struct shared_memory *shmem_ptr);

void shmem_put_data(struct shared_memory* shmem_ptr, char value);
bool shmem_get_data(struct shared_memory* shmem_ptr, char* value);

void shmem_end_comm(struct shared_memory* shmem_ptr);

#endif
