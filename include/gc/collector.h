#ifndef MICROVM_COLLECTOR_H
#define MICROVM_COLLECTOR_H

#include "allocator.h"

void mvm_gc_mark(mvm_obj_t* obj);
void mvm_gc_sweep(mvm_allocator_t* alloc);
size_t mvm_gc_collect(mvm_allocator_t* alloc);

#endif