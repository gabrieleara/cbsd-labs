#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>

#include <stdio.h>

#include "librpc.h"

__attribute__((noreturn)) void abort_error(char* str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

enum my_operation_t { OP_SUM = 0, OP_DIFF, OP_MUL, OP_DIV };

int32_t sum(int32_t a, int32_t b)
{
    return a+b;
}
int32_t diff(int32_t a, int32_t b)
{
    return a - b;
}
int32_t mul(int32_t a, int32_t b)
{
    return a * b;
}
int32_t divide(int32_t a, int32_t b)
{
    return a / b;
}

typedef int32_t (*fun_t) (int32_t, int32_t);

int make_call(struct rpc_message *message_ptr, int32_t* result)
{
    fun_t operation;

    switch((enum my_operation_t) message_ptr->operation)
    {
    case OP_SUM:
        operation = sum;
        break;
    case OP_DIFF:
        operation = diff;
        break;
    case OP_MUL:
        operation = mul;
        break;
    case OP_DIV:
        operation = divide;
        break;
    default:
        return -1;
    }

    *result = (*operation)(message_ptr->arg1, message_ptr->arg2);
    return 0;
}

int main(int argc, char* argv[])
{
    // Server configuration
    // char inet_address[] = "127.0.0.1";
    int port_number = 13994;
    int backlog = 10;

    // Use inet_address instead of NULL if necessary
    int listen_fd = server_create(NULL, port_number, backlog);

    if (listen_fd < 0)
    {
        perror("Function create_socket failed");
        exit(EXIT_FAILURE);
    }

    int client_fd;

    while ((client_fd = wait_for_client(listen_fd)) >= 0)
    {
        // TODO: should spawn a thread or a process

        struct rpc_message message;
        int32_t result;

        while (wait_for_rpc(client_fd, &message) >= 0)
        {
            if(make_call(&message, &result) < 0)
            {
                break;
            }

            send_result(client_fd, result);
        }

        close(client_fd);
    }

    close(listen_fd);
    return EXIT_SUCCESS;
}
