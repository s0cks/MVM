#include <stdio.h>
#include <stdlib.h>
#include <types/types.h>

int
mvm_integer_value(mvm_obj_t* obj){
    mvm_assert(mvm_is_integer(obj), "Not an integer");
    return mvm_to_integer(obj)->value;
}

double
mvm_double_value(mvm_obj_t* obj){
    mvm_assert(mvm_is_double(obj), "Not a double");
    return mvm_to_double(obj)->value;
}

byte
mvm_byte_value(mvm_obj_t* obj){
    mvm_assert(mvm_is_byte(obj), "Not a byte");
    return mvm_to_byte(obj)->value;
}

byte
mvm_bool_value(mvm_obj_t* obj){
    mvm_assert(mvm_is_bool(obj), "Not a bool");
    return mvm_to_bool(obj)->value;
}

mstring_t*
mvm_string_value(mvm_obj_t* obj){
    mvm_assert(mvm_is_string(obj), "Not a string");
    return mvm_to_string(obj)->value;
}

void
mvm_type_free(mvm_obj_t* obj){
    if(mvm_is_string(obj)){
        mvm_string_t* str = mvm_to_string(obj);
        mstring_free(str->value);
        free(str);
    } else if(mvm_is_double(obj)){
        mvm_double_t* dbl = mvm_to_double(obj);
        free(dbl);
    } else if(mvm_is_byte(obj)){
        mvm_byte_t* b = mvm_to_byte(obj);
        free(b);
    } else if(mvm_is_integer(obj)){
        mvm_integer_t* i = mvm_to_integer(obj);
        free(i);
    } else if(mvm_is_bool(obj)){
        mvm_bool_t* b = mvm_to_bool(obj);
        free(b);
    } else if(mvm_is_array(obj)){
        mvm_array_t* array = mvm_to_array(obj);
        for(size_t i = 0; i < array->len; i++){
            if(array->value[i] != NULL){
                mvm_type_free(array->value[i]);
            }
        }
        free(array);
    } else{
        printf("[MVM] Unknown Type\n");
        exit(1);
    }
}

mvm_obj_t*
mvm_array_at(mvm_obj_t* array, size_t index){
    mvm_assert(mvm_is_array(array), "Not an array");

    mvm_array_t* arr = mvm_to_array(array);
    if(index < 0 || index > arr->len){
        printf("[MVM] IndexOutOfBounds: %lu/%lu\n", index, mvm_array_len(array));
        exit(1);
    }

    return arr->value[index];
}

void
mvm_array_resize(mvm_obj_t* array, size_t nsize){
    mvm_assert(mvm_is_array(array), "Not an array");

    mvm_array_t* arr = mvm_to_array(array);
    if(arr->len > nsize){
        return;
    }

    size_t nlen = arr->len + 1;
    while(nlen < nsize){
        nlen += 1;
    }

    mvm_obj_t** nvalue;
    if((nvalue = realloc(arr->value, nlen)) == NULL){
        return;
    }

    arr->value = nvalue;
    arr->len = nlen;
}

void
mvm_array_push(mvm_obj_t* array, mvm_obj_t* value){
    mvm_assert(mvm_is_array(array), "Not an array");

    mvm_array_t* arr = mvm_to_array(array);
    if(arr->size + 1 > arr->len){
        mvm_array_resize(array, arr->len + 1);
    }

    arr->value[arr->size++] = value;
}