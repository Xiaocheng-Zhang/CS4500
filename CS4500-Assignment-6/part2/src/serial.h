// #include <stdlib.h>
// #include <stdio.h>
#pragma once
#include <stdarg.h>
#include <sys/socket.h>

#include "object.h"
#include "string.h"
#include "vec.h"

class StringArray : public Svec {
public:
  StringArray() : Svec() {}
};

class DoubleArray {

  double *vals_;
  size_t size_;
  size_t capacity_;
  DoubleArray() {
    size_ = 0;
    capacity_ = 0;
    vals_ = new double[capacity_];
  }
  DoubleArray(int n, ...) {
    size_ = n;
    capacity_ = 2 * n;
    vals_ = new double[capacity_];
    va_list vl;
    double val;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
      val = va_arg(vl, double);
      vals_[i] = val;
    }
    va_end(vl);
  }
};

enum class MsgKind {
  Ack,
  Nack,
  Put,

  Reply,
  Get,
  WaitAndGet,
  Status,

  Kill,
  Register,
  Directory
};

class Message : public Object {
public:
  MsgKind kind_; // the message kind

  size_t sender_; // the index of the sender node

  size_t target_; // the index of the receiver node

  size_t id_; // an id t unique within the node
};

class Ack : public Message {};

class Status : public Message {

  String *msg_; // owned
};

class Register : public Message {

  // sockaddr_in client;

  size_t port;
};

class Directory : public Message {

  size_t client;

  size_t *ports; // owned

  String **addresses; // owned; strings owned
};