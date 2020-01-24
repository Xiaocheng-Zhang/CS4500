#pragma once
#include "object.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

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
            //initialize(data);
            size_ = 0;
            capacity_ = 4;
        }

        ~Hashmap() {
            delete [] data;
        }

        void initialize(Hashmap_pair **new_data) {
            
        }

        size_t hash_index(Object *key) {
            
        }



        void hashmap_put(Hashmap_pair **temp_data, Object *key, Object *val) {
            
        }

        void expand() {
            
        }

        //get the exact data (not a copy) from Hashmap.
        //return null if no key inside.
        Object* get(Object *key) {
            
        }

        void put(Object *key, Object *val) {
            
        }

        void remove(Object *key) {
            
        }

        size_t size() {

        }

        Object** key_array() {
            
        }

        virtual void print_self() {
            
        }
};
