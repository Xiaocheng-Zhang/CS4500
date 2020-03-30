#pragma once
#include <iostream>
#include <unordered_map>

#include "object.h"
#include "string.h"

using namespace std;

/**
 * Key is type that used to represent the value's name and other information.
 * Each Key contains a char* name which is the key's name.
 * a size_t size which represent the length of key's name.
 * Not use a String because we tried to avoid code duplication.
 * Home address that used to check whether the key should be saved in this
 * current application.
 */
class Key : public Object {
private:
  char *name_;
  size_t size_;
  size_t home_address;

public:
  /**
   * Default Key constructor. Do nothing. Should never be used.
   */
  Key() : Object() {}

  /** Key constructor that save the input char* as the name of the key, size_t
   * as the id of application.*/
  Key(const char *name, size_t home_add) : Object() {
    name_ = (char *)name;
    home_address = home_add;
    size_ = strlen(name);
  }

  /** Remains empty since name is from a const char* type.*/
  ~Key() {}

  /**
   * A Simple getter method that used to get the name of key.*/
  char *get_name() { return name_; }

  /** hash_me method from the Object class.*/
  size_t hash_me() {
    size_t hash = 0;
    for (size_t i = 0; i < size_; ++i)
      hash = name_[i] + (hash << 6) + (hash << 16) - hash;
    return hash;
  }

  /**
   * Get the home address of current key.
   */
  virtual size_t get_home_address() { return home_address; }
};

/**
 * Key Value Store class. Allowed Application to save the data and get data from
 * other opend Application.
 */
template <class T> class KVStore : public Object {
private:
  unordered_map<char *, T> node_map;
  size_t home_address;

public:
  bool request_check;
  Key request_key;
  T request_value;
  /**
   * Default construtor without a input home address.
   */
  KVStore() : Object() {
    home_address = 0;
    request_check = false;
    request_value = nullptr;
  }

  /**
   * Default construtor with a input home address value.
   */
  KVStore(size_t idx) : Object() {
    home_address = idx;
    request_check = false;
    request_value = nullptr;
  }

  ~KVStore() { delete request_value; }

  /**
   * Put the Key and type T value into the KVStore.
   * used unordered map to save data.
   */
  void put(Key *k, T t) {
    size_t id = k->get_home_address();
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

  /**
   * get the Key from other connected KVStore ran by other Application.
   */
  T waitAndGet(Key k) {}

  /**
   * get the type T value from this current Node.
   */
  T get(Key k) { return node_map.at(k.get_name()); }

  /**
   * get the type T value from this current Node.
   */
  T get(char *c) { return node_map.at(c); }
};