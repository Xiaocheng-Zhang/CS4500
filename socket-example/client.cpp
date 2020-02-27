// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) {
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    const char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)  { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }

    send(sock , hello , strlen(hello) , 0 );
    valread = read(sock , buffer, 1024); 
    printf("Server said: %s\n", buffer);

    // Server should ask us to talk to it
    if ((valread = read(sock , buffer, sizeof(buffer) - 1)) > 0) { 
      buffer[valread] = '\0';
      printf("Server said: %s\n", buffer);
    }

    // Let the user enter messages for the server - keep reading from stdin
    // until EOF (Ctrl-D)
    while (fgets(buffer, sizeof(buffer), stdin)) {
      send(sock, buffer, strlen(buffer), 0);
      if ((valread = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[valread] = '\0';
        printf("Server replied: %s\n", buffer);
      }
    }
    
    printf("Done.\n");
    close(sock);
    return 0; 
} 
