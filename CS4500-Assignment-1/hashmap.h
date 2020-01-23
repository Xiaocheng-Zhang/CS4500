#pragma once
#include "object.h"
#include "string.h"
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

        void hashmap_put(Hashmap_pair **temp_data, Object *key, Object *val) {
            //index is the index made by hashcode mod capacity - 1
            //might exist a same, so put into next available cell.
            int index = hash_index(key);
            for (int i = index; i < capacity_; i++) {
                if (temp_data[i]) {
                    if (temp_data[i]->key_->equals(key)) {
                        temp_data[i]->val_ = val;
                        return;
                    }
                }
                if (!temp_data[i]) {
                    temp_data[i] = new Hashmap_pair(key, val);
                    return;
                }
            }
            for (int i = 0; i < index; i++) {
                if (temp_data[i]) {
                    if (temp_data[i]->key_->equals(key)) {
                        temp_data[i]->val_ = val;
                        return;
                    }
                }
                if (!temp_data[i]) {
                    temp_data[i] = new Hashmap_pair(key, val);
                    return;
                }
            }
        }

        void expand() {
            capacity_ *= 2;
            Hashmap_pair **temp = new Hashmap_pair*[capacity_];
            int i = 0;
            int count = 0;
            while (count < size_) {
                if (data[i]) {
                    hashmap_put(temp, data[i]->key_, data[i]->val_);
                    count++;
                }
                i++;
            }
            delete [] data;
            data = temp;
        }

        //check does the map has that key.
        int has(Object *key) {
            int index = hash_index(key);
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
            return false;
        }

        //get the exact data (not a copy) from Hashmap.
        //return null if no key inside.
        Object* get(Object *key) {
            int index = hash_index(key);
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
            return nullptr;
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

        virtual void print_self() {
            Object **keys = key_array();
            for (int i = 0; i < size_; i++) {
                printf("key: ");
                keys[i]->print_self();
                printf(" val: ");
                get(keys[i])->print_self();
                printf("\n");
            }
        }
};