#include <stdint.h>

// Protocol is fixed to TCP
int server_create(char *inet_address, int port, int backlog);

typedef int32_t operation_t;

struct rpc_message
{
    operation_t operation;
    int32_t arg1;
    int32_t arg2;
};

int wait_for_client(int listen_fd);

int wait_for_rpc(int comm_fd, struct rpc_message *message_ptr);

int send_result(int comm_fd, int32_t result);
