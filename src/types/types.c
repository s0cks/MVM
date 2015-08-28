#include <stdio.h>
#include <stdlib.h>
#include <types/types.h>

int
mvm_integer_value(mvm_obj_t* obj){
    if(mvm_is_integer(obj)){
        return mvm_to_integer(obj)->value;
    } else{
        printf("[MVM] Not an integer\n");
        exit(1);
    }
}

double
mvm_double_value(mvm_obj_t* obj){
    if(mvm_is_double(obj)){
        return mvm_to_double(obj)->value;
    } else{
        printf("[MVM] Not a double\n");
        exit(1);
    }
}

byte
mvm_byte_value(mvm_obj_t* obj){
    if(mvm_is_byte(obj)){
        return mvm_to_byte(obj)->value;
    } else{
        printf("[MVM] Not a byte\n");
        exit(1);
    }
}

mstring_t*
mvm_string_value(mvm_obj_t* obj){
    if(mvm_is_string(obj)){
        return mvm_to_string(obj)->value;
    } else{
        printf("[MVM] Not a string\n");
        exit(1);
    }
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
    } else{
        printf("[MVM] Unknown Type\n");
        exit(1);
    }
}