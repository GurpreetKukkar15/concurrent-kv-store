#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(void){
	int server_fd= socket(AF_INET, SOCK_STREAM, 0);

	if(server_fd== -1){
		perror("socket");
		return 1;
	}

	struct sockaddr_in server_address;
	server_address.sin_family= AF_INET;
	server_address.sin_port= htons(8080);
	int result= inet_pton(
		AF_INET,
		"127.0.0.1",
		&server_address.sin_addr
		);

	if (result != 1) {
    fprintf(stderr, "inet_pton failed\n");
    return 1;
	}



	if (bind(
        server_fd,
        (struct sockaddr *)&server_address,
        sizeof(server_address)
    ) == -1) {
    perror("bind");
    return 1;
}


	if (listen(server_fd, 10) == -1) {
    perror("listen");
    return 1;
}
	printf("Server is listening on 127.0.0.1:8080\n");



	printf("Waiting for a client...\n");
	int client_fd = accept(server_fd, NULL, NULL);

	if (client_fd == -1) {
    perror("accept");
    return 1;
}
	printf("Client connected! client_fd = %d\n", client_fd);


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



	char response[] = "OK";


	ssize_t bytes_sent = send(
    client_fd,
    response,
    strlen(response),
    0
	);

	if (bytes_sent == -1) {
    perror("send");
    return 1;
	}

	printf("Sent: %zd bytes\n", bytes_sent);


	ssize_t second_recv = recv(
    client_fd,
    buffer,
    sizeof(buffer) - 1,
    0
	);

	printf("Second recv returned: %zd\n", second_recv);

	printf("inet_pton result = %d\n", result);
	printf("server_fd= %d\n", server_fd);
	close(client_fd);
	close(server_fd);
	return 0;
}
