#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(void) {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        perror("socket");
        return 1;
    }
    printf("client_fd = %d\n", client_fd);


    struct sockaddr_in server_address;
    server_address.sin_family= AF_INET;
    server_address.sin_port= htons(8080);

    int result= inet_pton(
        AF_INET,
        "127.0.0.1",
        &server_address.sin_addr
    );
    if (result != 1){
        fprintf(stderr, "inet_pton failed..\n");
        return 1;
    }


    if (connect(
        client_fd,
        (struct sockaddr *)&server_address,
        sizeof(server_address)
    ) == -1) {
    perror("connect");
    return 1;
    }

    printf("Connected to server!\n");


    char message[] = "HELLO";

    ssize_t bytes_sent = send(
    client_fd,
    message,
    strlen(message),
    0
    );

    printf("bytes_sent = %zd\n", bytes_sent);



    char buffer[1024];

    ssize_t bytes_received = recv(
    client_fd,
    buffer,
    sizeof(buffer) - 1,
    0
    );

    if (bytes_received == -1) {
    perror("recv");
    return 1;
}

    buffer[bytes_received] = '\0';
    printf("Received: %s\n", buffer);
    close(client_fd);
    return 0;




}