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
            delete key_;
            delete val_;
        }
};

class Hashmap : public Object {
    private:
        Hashmap_pair **data;
        size_t size_;
        size_t capacity_; 

    public:
        Hashmap() {
            data = new Hashmap_pair*[4];
            capacity_ = 4;
            initialize(data);
            size_ = 0;
        }

        ~Hashmap() {
            delete [] data;
        }

        void initialize(Hashmap_pair **new_data) {
            for (size_t i = 0; i < capacity_; i++) {
                new_data[i] = nullptr;
            }
        }

        size_t hash_index(Object *key) {
            if (key) {
                return key->hash() & (capacity_ - 1);
            }
            return -1;
        }

        void hashmap_put(Hashmap_pair **temp_data, Object *key, Object *val) {
            //index is the index made by hashcode mod capacity - 1
            //might exist a same, so put into next available cell.
            size_t index = hash_index(key);
            for (size_t i = index; i < capacity_; i++) {
                if (temp_data[i]) {
                    if (temp_data[i]->key_->equals(key)) {
                        temp_data[i]->val_ = val;
                        return;
                    }
                }
                else {
                    temp_data[i] = new Hashmap_pair(key, val);
                    return;
                }
            }
            for (size_t i = 0; i < index; i++) {
                if (temp_data[i]) {
                    if (temp_data[i]->key_->equals(key)) {
                        temp_data[i]->val_ = val;
                        return;
                    }
                }
                else {
                    temp_data[i] = new Hashmap_pair(key, val);
                    return;
                }
            }
        }

        void expand() {
            capacity_ *= 2;
            Hashmap_pair **temp = new Hashmap_pair*[capacity_];
            initialize(temp);
            size_t i = 0;
            size_t count = 0;
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

        //get the exact data (not a copy) from Hashmap.
        //return null if no key inside.
        Object* get(Object *key) {
            size_t index = hash_index(key);
            for (size_t i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        return data[i]->val_;
                    }
                }
            }
            for (size_t i = 0; i < index; i++) {
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
                //puts("P");
            }
            //index is the index made by hashcode mod capacity - 1
            //might exist a same, so put into next available cell.
            size_t index = hash_index(key);
            for (size_t i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i]->val_ = val;
                        return;
                    }
                }
                else {
                    data[i] = new Hashmap_pair(key, val);
                    size_++;
                    return;
                }
            }
            for (size_t i = 0; i < index; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i]->val_ = val;
                        return;
                    }
                }
                else {
                    data[i] = new Hashmap_pair(key, val);
                    size_++;
                    return;
                }
            }
        }

        void remove(Object *key) {
            size_t index = hash_index(key);
            for (size_t i = index; i < capacity_; i++) {
                if (data[i]) {
                    if (data[i]->key_->equals(key)) {
                        data[i] = nullptr;
                    }
                }
            }
            for (size_t i = 0; i < index; i++) {
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
            size_t key_size = 0;
            for (size_t i = 0; i < capacity_; i++) {
                if (data[i]) {
                    keys[key_size] = data[i]->key_;
                    key_size++;
                }
            }
            return keys;
        }

        virtual void print_self() {
            Object **keys = key_array();
            for (size_t i = 0; i < size_; i++) {
                printf("key: ");
                keys[i]->print_self();
                printf(" val: ");
                get(keys[i])->print_self();
                printf("\n");
            }
        }
};