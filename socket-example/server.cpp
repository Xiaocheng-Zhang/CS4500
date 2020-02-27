// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, sock, valread;
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    struct sockaddr_in address;
    address.sin_family = AF_INET; 
    //address.sin_addr.s_addr = INADDR_ANY; 
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr) <= 0) {
      printf("Invalid address.\n");
      exit(EXIT_FAILURE);
    } 
    address.sin_port = htons( 8080 ); 
       
    // Attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *) &address,  
                                 sizeof(address)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    int addrlen = sizeof(address);
    if ((sock = accept(server_fd, (struct sockaddr *) &address,
                       (socklen_t *) &addrlen)) < 0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    char buffer[1024] = {0};
    valread = read(sock, buffer, sizeof(buffer) - 1);
    printf("Server received: %s\n",buffer ); 
    
    // Send hello
    const char *hello = "Hello from server";
    send(sock, hello , strlen(hello) , 0);

    // Start a one-sided conversation with the client
    const char *prompt = "Tell me something!";

    const char *replies[] = {
      "I hear you!",
      "You don't say!",
      "Wow! That blew my mind.",
      "Get outta here!",
      "I'm bored."
    };

    srand(time(NULL));

    // Send the prompt
    send(sock, prompt, strlen(prompt), 0);

    // Keep reading and replying until EOF
    while ((valread = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
      buffer[valread] = '\0';
      printf("Client said: %s\n", buffer);

      // Send a random reply
      const char* reply = replies[rand() % 5];
      send(sock, reply, strlen(reply), 0);
    }
    
    printf("Done.\n");
    close(sock);
    return 0; 
} 
