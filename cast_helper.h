#pragma once
//#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

String* cast_string(Object *object) {
    return dynamic_cast<String*>(object);
}

String** cast_object_arr(Object **array, int size) {
    String **output = new String*[size];
    for (int i = 0; i < size; i++) {
        output[i] = cast_string(array[i]);
    }
    return output;
}
