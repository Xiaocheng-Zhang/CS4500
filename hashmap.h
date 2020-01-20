#pragma once
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
//this is a general hashmap. I create it for practice and
//might be useful for future assignment.

class Hashmap_pair : public Object {
    public:
        Object* key_;
        Object* val_;

        Hashmap_pair(Object *key, Object *val) : Object() {
            key_ = key;
            val_ = val;
        }
        ~Hashmap_pair() {
        }
};

class Hashmap : public Object {
    private:
        Hashmap_pair **data;
        int size_;
        int capacity_;
        
    public:
        Hashmap() {
            data = new Hashmap_pair*[4];
            initialize(0);
            size_ = 0;
            capacity_ = 4;
        }

        ~Hashmap() {
            delete [] data;
        }

        int hash_index(Object *key) {
            if (key) {
                return key->hash() & (capacity_ - 1);
            }
            return -1;
        }

        void initialize(int index) {
            for (int i = index; i < capacity_; i++) {
                data[i] = nullptr;
            }
        }

        void expand() {
            capacity_ *= 2;
            Hashmap_pair **temp = new Hashmap_pair*[capacity_];
            for (int i = 0; i < size_; i++) {
                temp[i] = data[i];
            }
            delete [] data;
            data = temp;
            initialize(size_);
        }

        //check does the map has that key.
        int has(Object *key) {
            int index = hash_index(key);
            //if (data[index]) {
            for (int i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        return true;
                    }
                }
            }
            for (int i = 0; i < index; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        return true;
                    }
                }
            }
            //}
            return false;
        }

        //get the exact data (not a copy) from Hashmap.
        //return null if no key inside.
        Object* get(Object *key) {
            int index = hash_index(key);
            //if (data[index]) {
            for (int i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        return data[i]->val_;
                    }
                }
            }
            for (int i = 0; i < index; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        return data[i]->val_;
                    }
                }
            }
            //}
            return new Object();
        }

        void put(Object *key, Object *val) {
            if (size_ == capacity_) {
                expand();
            }
            //index is the index made by hashcode mod capacity - 1
            //might exist a same, so put into next available cell.
            int index = hash_index(key);
            for (int i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i]->val_ = val;
                        return;
                    }
                }
                if (!data[i]) {
                    data[i] = new Hashmap_pair(key, val);
                    size_++;
                    return;
                }
            }
            for (int i = 0; i < index; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i]->val_ = val;
                        return;
                    }
                }
                if (!data[i]) {
                    data[i] = new Hashmap_pair(key, val);
                    size_++;
                    return;
                }
            }
        }

        void remove(Object *key) {
            int index = hash_index(key);
            for (int i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i] = nullptr;
                    }
                }
            }
            for (int i = 0; i < index; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i] = nullptr;
                    }
                }
            }
        }

        size_t size() {
            return size_;
        }

        Object** key_array() {
            Object **keys;
            keys = new Object*[size_];
            int key_size = 0;
            for (int i = 0; i < capacity_; i++) {
                if (data[i]) {
                    keys[key_size] = data[i]->key_;
                    key_size++;
                }
            }
            return keys;
        }
};