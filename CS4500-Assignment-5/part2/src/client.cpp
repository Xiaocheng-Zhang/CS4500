// Client side C/C++ program to demonstrate Socket programming 
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

  while(1) {

    char message[20];
    fgets(message, 20, stdin);

    message[19] = '\0';

    send(sock, message, 20, 0);
  }


  close(sock);
}