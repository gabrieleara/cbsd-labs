#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>

#include <stdio.h>

__attribute__((noreturn)) void abort_error(char* str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    int sockfd;         // The socket on which we will listen to client connections
    int port = 13994;   // The port number on which we will listen for new connections

    struct sockaddr_in remote_addr; // The address of the remote client connected
    struct sockaddr_in local_addr;  // The address/port on which we will listen to;
                                    // in our case we won't care about which address
                                    // of the system we will receive the packet

    socklen_t socklen = sizeof(struct sockaddr_in); // The size of the sockaddr_in structure

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // A new TCP socket

    local_addr.sin_family = AF_INET;            // Internet address type
    local_addr.sin_port = htons(port);          // Port number
    local_addr.sin_addr.s_addr = INADDR_ANY;    // Any IP address

    // We bind the address specified to the listening socket
    int err = bind(sockfd, (struct sockaddr*) &local_addr, socklen);

    if (err != 0)
    {
        abort_error("BIND");
    }

    // We declare the socket as a passive socket (used only to accept)
    err = listen(sockfd, 1);

    if (err != 0)
    {
        abort_error("LISTEN");
    }

    // We set the remote_addr memory space to zeros
    memset(&remote_addr, 0, sizeof(struct sockaddr_in));

    while (1)
    {
        // The socket used to communicate with the accepted client, the address
        // will also be filled with the remote client address
        int comm_sock_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &socklen);

        printf("Accepted someone!\r\n");

        char c;

        // We read one character at the time, until the string is finished
        while (read(comm_sock_fd, &c, sizeof(char)) > 0)
        {
            if (c == '\0' || c == '\n' || c == '\r')
                break;

            putc(c, stdout);
        }

        printf("\r\n");

        close(comm_sock_fd);
    }

    // We never close the socket and all because the program never terminates
    // (if not abruptly closed)

}
