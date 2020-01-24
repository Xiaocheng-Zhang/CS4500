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
        //constructor
        Hashmap() {
            data = new Hashmap_pair*[4];
            //initialize(data);
            size_ = 0;
            capacity_ = 4;
        }

        // destructor
        ~Hashmap() {
            delete [] data;
        }

        // Initialize hashmap with null pointers
        void initialize(Hashmap_pair **new_data) {
            
        }

        // Return hash index given the key
        size_t hash_index(Object *key) {
            
        }


        // copy keys and values to a new Hashmap 
        void copy_to_new(Hashmap_pair **temp_data, Object *key, Object *val) {
            
        }

        // Double the capacity of hashmap when needed
        void expand() {
            
        }

        // Returns the value to which the specified key is mapped, 
        // or null if this map contains no mapping for the key.
        Object* get(Object *key) {
            
        }

        // Associates the specified value with the specified key in this map.
        void put(Object *key, Object *val) {
            
        }

        // Removes the mapping for the specified key from this map if present.
        void remove(Object *key) {
            
        }

        // Returns the number of key-value mappings in this map.
        size_t size() {

        }

        // Returns a list view of the keys contained in this map.
        Object** key_array() {
            
        }
};
