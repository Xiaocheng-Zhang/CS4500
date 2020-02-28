#pragma once
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <thread>

#include "object.h"
#include "vec.h"

#define PORT 8080
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_NUM 3

void client_speak(int core_fd) {
  while (1) {
    char buffer[4096];
    fgets(buffer, 4096, stdin);
    printf("client_speak: %s", buffer);
    send(core_fd, buffer, 4096, 0);
    if (!strcmp(buffer, "exit")) {
      exit(0);
    }
  }
}

void client_listen(int core_fd) {
  while (1) {
    char buffer[4096];
    int rv = read(core_fd, buffer, 4096);
    if (rv > 0) {
      puts(buffer);
    }
  }
}

void open_server(int core_fd, fd_set sockets, sockaddr_in address, int addrlen) {
  // specify the set
  FD_ZERO(&sockets);
  FD_SET(core_fd, &sockets);

  // open until manager wants to shut it down.
  while (1) {
    // copy the set
    fd_set copy = sockets;
    // puts("waiting for selecting");
    int socket_count = select(FD_SETSIZE, &copy, nullptr, nullptr, nullptr);
    for (int i = 0; i < socket_count; i++) {
      int socket = copy.fds_bits[i];
      if (socket == core_fd) {
        int client =
            accept(socket, (sockaddr *)&address, (socklen_t *)&addrlen);
        // std::cout << socket << " " << core_fd << " " << client;
        // exit(0);
        if (client == -1) {
          perror("accept");
          exit(EXIT_FAILURE);
        }
        // add the client fd to the set.
        FD_SET(client, &sockets);
        puts("pass");
        printf("client %d accept", client);
        char buffer[1024] = "Welcome to 我们的妙♂妙♂屋!\0";
        send(socket, buffer, 1024, 0);
      }
      else {
        char buffer[4096];
        int length = recv(socket, buffer, 4096, 0);
        if (length >= 0) {
          printf("read from buffer: ", buffer);
          if (!strcmp(buffer, DEFAULT_IP) || !strcmp(buffer, "exit")) {
            send(socket, "欢迎下次再来 我们的妙♂妙♂屋!\0", 20, 0);
            shutdown(socket, SHUT_RDWR);
            // delete this socekt from set.
            FD_CLR(socket, &sockets);
          }
        } else {
          // broadcast to all clients
          for (int i = 0; i < socket_count; i++) {
            int current = sockets.fds_bits[i];
            // don't send redundant info back to that client
            if (current != socket) {
              send(current, buffer, sizeof(buffer), 0);
            }
          }
        }
      }
    }
  }
}

class Core : public Object {
public:
  int core_fd, addrlen;
  struct sockaddr_in address;
  Core() : Object() {
    core_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (core_fd == -1) {
      perror("socket failed");
      exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    if (inet_pton(AF_INET, DEFAULT_IP, &address.sin_addr.s_addr) <= 0) {
      printf("Invalid address.\n");
      exit(EXIT_FAILURE);
    }
    address.sin_port = htons(PORT);
  }
  ~Core() {}
  virtual void call_bind() {
    if (bind(core_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }
    // set addrlen after using address
    addrlen = sizeof(address);
  }
  virtual void call_listen(size_t wait_list) {
    if (listen(core_fd, DEFAULT_NUM) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
  }

  virtual void call_connect() {
    if (connect(core_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      printf("\nConnection Failed \n");
      //exit(EXIT_FAILURE);
    }
  }
};

class Server : public Core {
public:
  // create initial values.
  fd_set sockets;
  // constructor with input number of maxium waiting list.
  Server(size_t wait_list) : Core() {
    call_bind();
    call_listen(wait_list);
    // set addrlen after using address
    // addrlen = sizeof(address);
  }

  // constructor without input number of maxium waiting list.
  Server() : Core() {
    call_bind();
    call_listen(DEFAULT_NUM);
    // set addrlen after using address
    // addrlen = sizeof(address);
  }

  ~Server() {}


  void start() {
    std::thread maintain_server(open_server, core_fd, sockets, address, addrlen);
    while (1) {
      char buffer[8];
      fgets(buffer, 8, stdin);
      // printf("server receive: %s %d\n", buffer, strncmp(buffer, "exit", 4));
      if (!strncmp(buffer, "exit", 4)) {
        break;
      } else {
        // broadcast to all clients.
      }
    }
    maintain_server.native_handle();
    close(core_fd);
  }
};

class Client : public Core {
public:
  Client() : Core() {
    //call_listen(DEFAULT_NUM);
    call_connect();
  }

  void start() {
    puts("connection started");
    std::thread open_chat(client_speak, core_fd);
    std::thread read_chat(client_listen, core_fd);
    open_chat.join();
    read_chat.native_handle();
  }
};
