#pragma once
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

#define PORT 8080
#define DEFAULT_IP "0619.1997.0525.2000"
class Core {
public:
    int server_fd, sock, valread;
    struct sockaddr_in address;
    Core() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        }
    }
};

class Client : public Core {};

class Server : public Core {};