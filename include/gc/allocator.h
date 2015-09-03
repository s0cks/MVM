#ifndef MICROVM_ALLOCATOR_H
#define MICROVM_ALLOCATOR_H

#include "../mvm-private.h"
#include "../types/types.h"

typedef struct{
    mvm_obj_t* head;

    size_t num_objects;
    size_t max_objects;
} mvm_allocator_t;

mvm_allocator_t* mvm_allocator_create(size_t max_objects);
mvm_obj_t* mvm_alloc_new_integer(mvm_allocator_t* alloc, int value);
mvm_obj_t* mvm_alloc_new_double(mvm_allocator_t* alloc, double value);
mvm_obj_t* mvm_alloc_new_byte(mvm_allocator_t* alloc, byte value);
mvm_obj_t* mvm_alloc_new_string(mvm_allocator_t* alloc, byte* value);
mvm_obj_t* mvm_alloc_new_bool(mvm_allocator_t* alloc, byte value);
void mvm_alloc_free(mvm_allocator_t* alloc);

#endif