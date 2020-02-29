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
  //int[3] clients;

  while(1) {

    readfds = fds;
    rc = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);

    if (rc == -1) {
      perror("Select");
      break;
    }

    for (i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET(i, &readfds)) {
        //std::cout << "ohhhh" << std::endl;
        if (i == serversock) {
          //std::cout << "why?" << std::endl;
          if (numsocks < maxsocks) {
            //std::cout << "Im going to receive client" << std::endl;
            clientsock[numsocks] = accept(serversock,
                                      (struct sockaddr *) &clientaddr,
                                      (socklen_t *)&clientaddrlen);
            if (clientsock[numsocks] == -1) perror("Accept");
            FD_SET(clientsock[numsocks], &fds);
            //std::cout << "Done!" << std::endl;

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
          std::cout << "Heard from " << i-3 << std::endl;
          //printf("%d\n", index);
          printf("%s\n", message);

          char real_mg[messageLength+1];
          real_mg[0] = i - 3 + '0';
          real_mg[1] = '-';
          real_mg[2] = '>';
          for (int i = 3; i < messageLength; i++) {
            real_mg[i] = message[i];
          }

          if (message[0] == '3') {
            send(6, real_mg, 20 ,0);
            std::cout << "Message Redirected" << std::endl;
          }
          else if (message[0] == '2'){
            send(5, real_mg, 20 ,0);
            std::cout << "Message Redirected" << std::endl;
          }
          else if (message[0] == '1'){
            send(4, real_mg, 20 ,0);
            std::cout << "Message Redirected" << std::endl;
          }
          else {
            std::cout << "No receiver is specified in this message" << std::endl;
          }
          
        }
      }
    }
  }

  close(serversock);
  return 0;
}