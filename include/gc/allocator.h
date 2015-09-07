#ifndef MICROVM_ALLOCATOR_H
#define MICROVM_ALLOCATOR_H

#include <types/mstringpool.h>
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
mvm_obj_t* mvm_alloc_new_intern_string(mvm_allocator_t* alloc, mstring_pool_t* pool, byte* value);
mvm_obj_t* mvm_alloc_new_bool(mvm_allocator_t* alloc, byte value);
mvm_obj_t* mvm_alloc_new_array(mvm_allocator_t* alloc, size_t len);
mvm_obj_t* mvm_alloc_new_null(mvm_allocator_t* alloc);
void mvm_alloc_free(mvm_allocator_t* alloc);

#endif