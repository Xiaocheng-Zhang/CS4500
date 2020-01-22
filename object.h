#pragma once
#include <iostream>

class Object {
    public:
        Object() {
            hash_code = 0;
            hash();
        }

        ~Object() {}

        virtual bool equals(Object *object) {
            return this == object;
        }

        virtual size_t hash() {
            if (hash_code == 0) {
                hash_me();
            }
            return hash_code;
        }

        virtual void hash_me() {
            hash_code = (size_t) this;
        }

        virtual void print_self() {
            //print nothing
        }
    private:
        size_t hash_code;
};