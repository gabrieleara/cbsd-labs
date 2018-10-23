#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// The size of the sockaddr_in structure
#define SOCK_LEN (sizeof(struct sockaddr_in))

// Protocol is fixed to TCP
int server_create(char* inet_address, int port, int backlog)
{
    int ret;                        // The return value of each function
    int af_type = AF_INET;          // The type of the socket communication
    struct sockaddr_in local_addr;  // The address/port on which we will accept
    int listen_fd;                  // The fd used to accept
    int protocol = SOCK_STREAM;     // The protocol used to communicate

    local_addr.sin_family = af_type;   // Network address type
    local_addr.sin_port = htons(port); // Port number

    if (inet_address == NULL)
    {
        // We don't care about which address will receive the connect
        local_addr.sin_addr.s_addr = INADDR_ANY; // Any IP address
    }
    else
    {
        // We convert the text-based address in a network address
        if(inet_pton(af_type, inet_address, &local_addr.sin_addr.s_addr) == 0)
            return -1;
    }

    // Creating a new socket
    ret = socket(af_type, protocol, 0);

    if (ret < 0)
        return ret;

    listen_fd = ret;

    // Binding the address/port to the socket
    ret = bind(listen_fd, (struct sockaddr *) &local_addr, SOCK_LEN);

    if (ret)
        return ret;

    // Marking the socket as passive TCP socket
    ret = listen(listen_fd, backlog);

    if (ret)
        return ret;

    return listen_fd;
}

typedef int32_t operation_t;

struct rpc_message
{
    operation_t operation;
    int32_t arg1;
    int32_t arg2;
};

#define SIZE_MESSAGE (sizeof(struct rpc_message))

int wait_for_client(int listen_fd)
{
    struct sockaddr_in remote_addr;
    unsigned int sock_len = SOCK_LEN; // TODO: should I assign it myself or not?

    memset(&remote_addr, 0, SOCK_LEN);

    return accept(listen_fd, (struct sockaddr *)&remote_addr, &sock_len);
}

int wait_for_rpc(int comm_fd, struct rpc_message* message_ptr)
{
    int remaining = SIZE_MESSAGE;
    int how_many_recv = 0;
    unsigned char* buffer_ptr = (unsigned char*) message_ptr;

    while(remaining > 0 && (how_many_recv = read(comm_fd, buffer_ptr, remaining)) > 0)
    {
        remaining -= how_many_recv;
        buffer_ptr += how_many_recv;
    }

    if (remaining != 0)
        return -1;

    message_ptr->operation = ntohl(message_ptr->operation);
    message_ptr->arg1 = ntohl(message_ptr->arg1);
    message_ptr->arg2 = ntohl(message_ptr->arg2);

    return 0;
}

int send_result(int comm_fd, int32_t result)
{
    result = htonl(result);
    unsigned char* buffer_ptr = (unsigned char*) &result;
    int remaining = sizeof(int32_t);
    int how_many_sent;

    while (remaining > 0 && (how_many_sent = write(comm_fd, buffer_ptr, remaining)) > 0)
    {
        remaining -= how_many_sent;
        buffer_ptr += how_many_sent;
    }

    if (remaining != 0)
        return -1;

    return 0;
}
