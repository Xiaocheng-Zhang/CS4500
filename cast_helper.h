#pragma once
#include "string.h"
#include "list.h"
#include "object.h"

String* cast_string(Object *object) {
    return dynamic_cast<String*>(object);
}

StrList* cast_list(Object *object) {
    return dynamic_cast<StrList*>(object);
}

String** cast_object_arr(Object **array, int size) {
    String **output = new String*[size];
    for (int i = 0; i < size; i++) {
        output[i] = cast_string(array[i]);
    }
    return output;
}
