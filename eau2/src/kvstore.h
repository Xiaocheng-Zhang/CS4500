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
  size_t id_;

public:
  Key() : Object() {}

  Key(const char *name, size_t id) : Object() {
    name_ = strdup(name);
    id_ = id;
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

  virtual size_t get_id() { return id_; }
};

class CompactKey : public Key {
private:
  size_t id_;
  size_t position_;

public:
  CompactKey(size_t id, size_t position) : Key() {
    id_ = id;
    position_ = position;
  }

  size_t get_position() { return position_; }

  size_t get_id() { return id_; }
};

class KeyList : public Object {
private:
  unordered_map<const char *, CompactKey *> key_map;

public:
  KeyList() : Object() { }
  void add_key(Key *k) {
    CompactKey *tmp = new CompactKey(k->get_id(), k->get_position());
    key_map[k->get_name()] = tmp;
  }

  CompactKey *get_CompactKey_from_name(char *c) {
    if (key_map.find(c) == key_map.end()) {
      cout << "can't find a key called " << c << " in this KeyList\n";
      exit(1);
    }
    return key_map.at(c);
  }
};

template <class T> class Node : public Object {
private:
  // size_t is position
  unordered_map<size_t, T> data_map;

public:
  Node() : Object() {}

  void put(size_t position, T t) { data_map.insert({position, t}); }

  T get(size_t position) { return data_map.at(position); }
};

template <class T> class NodeList : public Object {
private:
  // size_t is node id
  unordered_map<size_t, Node<T> *> node_map;

public:
  NodeList() : Object() {}
  void put_to_node(size_t id, size_t position, T t) {
    auto it = node_map.find(id);
    if (it == node_map.end()) {
      Node<T> *temp = new Node<T>();
      temp->put(position, t);
      node_map.insert({id, temp});
    } else {
      node_map[id]->put(position, t);
    }
  }

  T get_from_node(size_t id, size_t position) {
    /**
     * key exist:
     *
     * not exist:
     */
    auto it = node_map.find(id);
    if (it == node_map.end()) {
      printf("Data not found in node_id %ld position %ld", id, position);
      return nullptr;
    }
    return node_map.at(id)->get(position);
  }
};

template <class T> class KVStore : public Object {
private:
  KeyList *keys_;
  NodeList<T> *nodes_;
  size_t idx_;

public:
  KVStore() : Object() {
    idx_ = 0;
    keys_ = new KeyList();
    nodes_ = new NodeList<T>();
  }
  KVStore(size_t idx) : Object() {
    idx_ = idx;
    keys_ = new KeyList();
    nodes_ = new NodeList<T>();
  }

  ~KVStore() {
    delete keys_;
    delete nodes_;
  }

  // translate key into size_t which saved memory.
  // put value into the node which signed by Key.
  void put(Key *k, T t) {
    size_t id = k->get_id();
    keys_->add_key(k);
    puts("put to node");
    nodes_->put_to_node(id, k->get_position(), t);
  }

  // get type T from Key's id.
  T get(Key k) { return nodes_->get_from_node(k.get_id(), k.get_position()); }

  // get type T without knowing node id.
  T get(char *c) {
    CompactKey *tmp = keys_->get_CompactKey_from_name(c);
    return nodes_->get_from_node(tmp->get_id(), tmp->get_position());
  }
};