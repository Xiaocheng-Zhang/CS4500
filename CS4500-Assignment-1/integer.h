#pragma once
#include "object.h"

class Integer : public Object {
    public: 
    //int val_;
    Integer(int val) : Object() {
        val_ = val;
        hash_code = 0;
    }

    virtual void print_self() {
        printf("%d", val_);
    }

    virtual bool equals(Object *object) {
        Integer *integer = dynamic_cast<Integer*>(object);
        if (!integer) {
            return false;
        }
        return integer->val_ == val_;
    }

    virtual size_t hash() {
        if (hash_code == 0) {
            hash_me();
        }
        return hash_code;
    }

    virtual void hash_me() {
        hash_code = val_;
    }

    int val_;
    int hash_code;
};