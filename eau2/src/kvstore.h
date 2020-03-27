#pragma once
#include <iostream>
#include <unordered_map>

#include "object.h"
#include "string.h"

using namespace std;

class Key : public Object {
private:
  const char *name_;
  size_t size_;
  size_t home_address;

public:
  Key() : Object() {}

  Key(const char *name, size_t home_add) : Object() {
    name_ = strdup(name);
    home_address = home_add;
    size_ = strlen(name);
  }

  ~Key() { delete[] name_; }

  const char *get_name() { return name_; }

  size_t hash_me() {
    size_t hash = 0;
    for (size_t i = 0; i < size_; ++i)
      hash = name_[i] + (hash << 6) + (hash << 16) - hash;
    return hash;
  }

  virtual size_t get_position() { return hash(); }

  virtual size_t get_id() { return home_address; }
};

class CompactKey : public Key {
private:
  size_t home_address;
  size_t position_;

public:
  CompactKey(size_t id, size_t position) : Key() {
    home_address = id;
    position_ = position;
  }

  size_t get_position() { return position_; }

  size_t get_id() { return home_address; }
};

class KeyList : public Object {
private:
  unordered_map<const char *, CompactKey *> *key_map;

public:
  KeyList() : Object() {
    key_map = new unordered_map<const char *, CompactKey *>();
  }

  ~KeyList() { delete key_map; }
  void add_key(Key *k) {
    key_map->insert(
        {k->get_name(), new CompactKey(k->get_id(), k->get_position())});
    cout << key_map->at(k->get_name())->get_position() << "\n";
  }

  CompactKey *get_CompactKey_from_name(const char *c) {
    if (key_map->find(c) == key_map->end()) {
      cout << "can't find a key called " << c << " in this KeyList\n";
      exit(1);
    }
    return key_map->at(c);
  }
};

template <class T> class Node : public Object {
private:
  // size_t is position
  unordered_map<const char *, T> data_map;

public:
  Node() : Object() {}

  ~Node() {}

  void put(const char *name, T t) {
    // will stuck here
    data_map.insert({name, t});
  }

  T get(const char *name) { return data_map.at(name); }
};

// template <class T> class NodeList : public Object {
// private:
//   // size_t is node id
//   size_t start_idx;
//   vector<Node<T> *> node_vec;

// public:
//   NodeList(size_t idx) : Object() { start_idx = idx; }
//   void put_to_node(size_t id, size_t position, T t) {
//     assert(id - start_idx >= 0);
//     // auto it = node_map.find(id);
//     // if (it == node_map.end()) {
//     //   Node<T> temp;
//     //   temp.put(position, t);
//     //   puts("start");
//     //   node_map.insert({id, temp});
//     // } else {
//     //   node_map[id].put(position, t);
//     // }
//   }

//   T get_from_node(size_t id, size_t position) {
//     /**
//      * key exist:
//      *
//      * not exist:
//      */
//     // auto it = node_map.find(id);
//     // if (it == node_map.end()) {
//     //   printf("Data not found in node_id %ld position %ld", id, position);
//     //   return nullptr;
//     // }
//     // return node_map.at(id).get(position);
//   }
// };

template <class T> class KVStore : public Object {
private:
  KeyList *keys_;
  Node<T> *node_;
  size_t home_address;

public:
  KVStore() : Object() {
    home_address = 0;
    keys_ = new KeyList();
    node_ = new Node<T>();
  }
  KVStore(size_t idx) : Object() {
    home_address = idx;
    keys_ = new KeyList();
    node_ = new Node<T>();
  }

  ~KVStore() {
    delete keys_;
    delete node_;
  }

  // translate key into size_t which saved memory.
  // put value into the node which signed by Key.
  void put(Key *k, T t) {
    size_t id = k->get_id();
    if (id == home_address) {
      keys_->add_key(k);
      node_->put(k->get_name(), t);
    } else {
      cout << "Skip the KVStore " << home_address << "\n";
    }
  }

  // get type T from Key's id.
  T get(Key k) { return node_->get(k.get_name()); }

  // get type T without knowing node id.
  T get(char *c) {
    CompactKey *tmp = keys_->get_CompactKey_from_name(c);
    return node_->get(tmp->get_name());
  }
};