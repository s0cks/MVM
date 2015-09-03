#include <stdlib.h>
#include <types/types.h>
#include <gc/allocator.h>
#include "gc/collector.h"

mvm_allocator_t*
mvm_allocator_create(size_t max_objects){
    mvm_allocator_t* alloc = malloc(sizeof(mvm_allocator_t));
    alloc->max_objects = max_objects;
    alloc->num_objects = 0;
    alloc->head = NULL;
    return alloc;
}

mvm_obj_t*
mvm_alloc_new_integer(mvm_allocator_t* alloc, int value){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_integer_t* integer;
    if((integer = malloc(sizeof(mvm_integer_t))) == NULL){
        return NULL;
    }

    integer->value = value;
    integer->obj.type = MVM_INTEGER;
    integer->obj.marked = 0;
    integer->obj.next = alloc->head;

    alloc->head = &integer->obj;
    alloc->num_objects++;
    return &integer->obj;
}

mvm_obj_t*
mvm_alloc_new_double(mvm_allocator_t* alloc, double value){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_double_t* dbl;
    if((dbl = malloc(sizeof(mvm_double_t))) == NULL){
        return NULL;
    }

    dbl->value = value;
    dbl->obj.type = MVM_DOUBLE;
    dbl->obj.marked = 0;
    dbl->obj.next = alloc->head;
    alloc->head = &dbl->obj;
    alloc->num_objects++;
    return &dbl->obj;
}

mvm_obj_t*
mvm_alloc_new_byte(mvm_allocator_t* alloc, byte value){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_byte_t* b;
    if((b = malloc(sizeof(mvm_byte_t))) == NULL){
        return NULL;
    }

    b->value = value;
    b->obj.type = MVM_BYTE;
    b->obj.marked = 0;
    b->obj.next = alloc->head;
    alloc->head = &b->obj;
    alloc->num_objects++;
    return &b->obj;
}

mvm_obj_t*
mvm_alloc_new_bool(mvm_allocator_t* alloc, byte value){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_bool_t* b;
    if((b = malloc(sizeof(mvm_bool_t))) == NULL){
        return NULL;
    }

    b->value = value;
    b->obj.type = MVM_BOOL;
    b->obj.marked = 0;
    b->obj.next = alloc->head;
    alloc->head = &b->obj;
    alloc->num_objects++;
    return &b->obj;
}

mvm_obj_t*
mvm_alloc_new_string(mvm_allocator_t* alloc, byte* value){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_string_t* str;
    if((str = malloc(sizeof(mvm_string_t))) == NULL){
        return NULL;
    }

    str->value = mstring_wrap(value);
    str->obj.type = MVM_STRING;
    str->obj.marked = 0;
    str->obj.next = alloc->head;
    alloc->head = &str->obj;
    alloc->num_objects++;
    return &str->obj;
}

mvm_obj_t*
mvm_alloc_new_array(mvm_allocator_t* alloc, size_t len){
    if(alloc->num_objects == alloc->max_objects){
        mvm_gc_collect(alloc);
    }

    mvm_array_t* array;
    if((array = malloc(sizeof(mvm_array_t))) == NULL){
        return NULL;
    }

    if((array->value = malloc(sizeof(mvm_obj_t*) * len)) == NULL){
        free(array);
        return NULL;
    }

    for(size_t i = 0; i < len; i++){
        array->value[i] = NULL;
    }

    array->len = len;
    array->size = 0;
    array->obj.type = MVM_ARRAY;
    array->obj.marked = 0;
    array->obj.next = alloc->head;
    alloc->head = &array->obj;
    alloc->num_objects++;
    return &array->obj;
}

void
mvm_alloc_free(mvm_allocator_t* alloc){
    mvm_gc_collect(alloc);
    free(alloc);
}