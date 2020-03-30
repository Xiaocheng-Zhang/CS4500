#pragma once
#include <iostream>
#include <unordered_map>

#include "object.h"
#include "string.h"

using namespace std;

class Key : public Object {
private:
  char *name_;
  size_t size_;
  size_t home_address;

public:
  Key() : Object() {}

  Key(const char *name, size_t home_add) : Object() {
    name_ = (char*) name;
    home_address = home_add;
    size_ = strlen(name);
  }

  ~Key() {
    //delete name_;
   }

  char *get_name() { return name_; }

  size_t hash_me() {
    size_t hash = 0;
    for (size_t i = 0; i < size_; ++i)
      hash = name_[i] + (hash << 6) + (hash << 16) - hash;
    return hash;
  }

  virtual size_t get_position() { return hash(); }

  virtual size_t get_id() { return home_address; }
};

template <class T> class KVStore : public Object {
private:
  unordered_map<char *, T> node_map;
  size_t home_address;

public:
  KVStore() : Object() {
    home_address = 0;
  }
  KVStore(size_t idx) : Object() {
    home_address = idx;
  }

  ~KVStore() {}

  // translate key into size_t which saved memory.
  // put value into the node which signed by Key.
  void put(Key *k, T t) {
    size_t id = k->get_id();
    if (id == home_address) {
      // check if the key exist
      char *k_name = k->get_name();
      auto it = node_map.find(k_name);
      if (it == node_map.end()) {
        // not exist
        node_map.insert({k_name, t});
        
      }
      // if exist, do nothing since we mustn't mutation
    } else {
      cout << "Skip the KVStore " << home_address << "\n";
      // do something serialize and network stuff
    }
  }

  T waitAndGet(Key k) {}

  // get type T from Key's id.
  T get(Key k) { return node_map.at(k.get_name()); }

  // get type T without knowing node id.
  T get(char *c) { return node_map.at(c); }
};