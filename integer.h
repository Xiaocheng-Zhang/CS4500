#pragma once
#include "object.h"

class Integer : public Object {
    public: 
    int val_;
    Integer(int val) : Object() {
        val_ = val;
    }
};