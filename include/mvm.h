#ifndef MICROVM_MVM_H
#define MICROVM_MVM_H

#include "mvm-private.h"
#include "types/types.h"
#include "types/mstringpool.h"
#include "types/mclass.h"
#include "gc/allocator.h"
#include "gc/collector.h"
#include "opcodes.h"

#ifndef MVM_SS
#define MVM_SS 1024
#endif

typedef struct{
    mvm_obj_t* stack[MVM_SS];
    size_t stack_size;
    mvm_allocator_t* alloc;
    mstring_pool_t* string_pool;
} mvm_t;

mvm_t* mvm_create() __attribute__((malloc));

mvm_obj_t* mvm_push_string(mvm_t* mvm, byte* data);
mvm_obj_t* mvm_push_intern_string(mvm_t* mvm, byte* data);
mvm_obj_t* mvm_push_double(mvm_t* mvm, double data);
mvm_obj_t* mvm_push_integer(mvm_t* mvm, int data);
mvm_obj_t* mvm_push_byte(mvm_t* mvm, byte data);
mvm_obj_t* mvm_push_bool(mvm_t* mvm, byte data);
mvm_obj_t* mvm_push_null(mvm_t* mvm);

mvm_obj_t* mvm_pop(mvm_t* mvm);

size_t mvm_gc(mvm_t* mvm);
void mvm_free(mvm_t* mvm);
void mvm_run(mvm_t* mvm);

#endif