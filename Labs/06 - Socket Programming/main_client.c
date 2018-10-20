#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>

// int socket(int domain, int type, int protocol);

#define MY_PORT (13994)

__attribute__((noreturn)) void aborte(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    int sockfd; // Client socket descriptor

    char address[] = "127.0.0.1";   // Address of the server
    int port = 13994;               // Server listening port

    struct sockaddr_in remote_addr; // The address/port of the server

    char message[128]; // The message we will send to the server

    // Create a new socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // We now set up everything for the server address/port
    remote_addr.sin_family = AF_INET;   // Internet address type
    remote_addr.sin_port = htons(port); // Our listening port

    // This function converts from dotted notation to internet address binary
    if (inet_pton(AF_INET, address, &remote_addr.sin_addr.s_addr) == 0)
    {
        aborte("INET_ATON");
    }

// DEBUG
    // Let's check that the address is correct:
    char address_check[16];
    inet_ntop(AF_INET, &remote_addr.sin_addr.s_addr, address_check, sizeof(remote_addr));
    printf("Check that this address is correct: %s\r\n", address_check);
// END DEBUG

    // The server will deliver a message to the client who will request it
    printf("Insert the message and press enter (max. 120 ch) : ");
    // fflush(stdout); // Unnecessary since we call scanf

    scanf("%s", &message[0]);

    // We connect to the server
    int err = connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(remote_addr));

    if (err == 0)
        printf("Connected!");
    else
        aborte("CONNECT");

    // We send a message to the server we connected to
    write(sockfd, message, sizeof(message));



    // We close both the connection and the socket
    close(sockfd);
}
