#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>

int main(int argc, char **argv) {

  struct sockaddr_in servaddr;
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (sock == -1) perror("Socket");

  bzero((void *) &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6782);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (-1 == connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    perror("Connect");

  pid_t pid = fork();
  
  if (pid == 0) {
    while (1) {
      char message[20];
      fgets(message, 20, stdin);
      message[19] = '\0';
      send(sock, message, 20, 0);
    }
    
  }
  else if (pid >0) {
    while (1) {
      char buffer[1024] = {0};
      int valread = read(sock, buffer, sizeof(buffer) - 1);
      printf("Server received: %s\n",buffer ); 
    }
  }
  else {
    std::cout << "fork failed" << std::endl;
  }
  // while(1) {

  //   char message[20];
  //   fgets(message, 20, stdin);

  //   message[19] = '\0';

  //   send(sock, message, 20, 0);
  //   char buffer[1024] = {0};
  //   int valread = read(sock, buffer, sizeof(buffer) - 1);
  //   printf("Server received: %s\n",buffer ); 
  // }



  close(sock);
}