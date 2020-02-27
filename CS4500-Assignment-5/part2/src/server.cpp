// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#define PORT 8080 
int main(int argc, char **argv) {

  fd_set fds, readfds;
  int i, clientaddrlen;
  int clientsock[2], rc, numsocks = 0, maxsocks = 3;

  int serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serversock == -1) perror("Socket");

  struct sockaddr_in serveraddr, clientaddr;  
  bzero(&serveraddr, sizeof(struct sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(6782);

  if (-1 == bind(serversock, (struct sockaddr *)&serveraddr, 
                 sizeof(struct sockaddr_in))) 
    perror("Bind");

  if (-1 == listen(serversock, SOMAXCONN))
    perror("Listen");

  FD_ZERO(&fds);
  FD_SET(serversock, &fds);

  while(1) {

    readfds = fds;
    rc = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);

    if (rc == -1) {
      perror("Select");
      break;
    }

    for (i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET(i, &readfds)) {
        if (i == serversock) {
          if (numsocks < maxsocks) {
            clientsock[numsocks] = accept(serversock,
                                      (struct sockaddr *) &clientaddr,
                                      (socklen_t *)&clientaddrlen);
            if (clientsock[numsocks] == -1) perror("Accept");
            FD_SET(clientsock[numsocks], &fds);
            numsocks++;
          } else {
            printf("Ran out of socket space.\n");

          }
        } else {
          int messageLength = 19;
          char message[messageLength+1];
          int in, index = 0, limit = messageLength+1;

          while ((in = recv(i, &message[index], limit, 0)) > 0) {
            index += in;
            limit -= in;
          }

          //printf("%d\n", index);
          printf("%s\n", message);

        }
      }
    }
  }

  close(serversock);
  return 0;
}