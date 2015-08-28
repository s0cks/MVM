#include <mvm.h>
#include <gc/collector.h>

mvm_t*
mvm_create(){
    mvm_t* mvm;
    if((mvm = malloc(sizeof(mvm_t))) == NULL){
        return NULL;
    }

    mvm->alloc = mvm_allocator_create(MVM_SS);
    mvm->stack_size = 0;
    return mvm;
}

mvm_obj_t*
mvm_push_string(mvm_t* mvm, byte* data){
    mvm_obj_t* str;
    if((str = mvm_alloc_new_string(mvm->alloc, data)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("[MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = str;
    return str;
}

mvm_obj_t*
mvm_push_double(mvm_t* mvm, double data){
    mvm_obj_t* dbl;
    if((dbl = mvm_alloc_new_double(mvm->alloc, data)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("[MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = dbl;
    return dbl;
}

mvm_obj_t*
mvm_push_integer(mvm_t* mvm, int data){
    mvm_obj_t* i;
    if((i = mvm_alloc_new_integer(mvm->alloc, data)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("[MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = i;
    return i;
}

mvm_obj_t*
mvm_push_byte(mvm_t* mvm, byte data){
    mvm_obj_t* b;
    if((b = mvm_alloc_new_byte(mvm->alloc, data)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("]MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = b;
    return b;
}

mvm_obj_t*
mvm_pop(mvm_t* mvm){
    if(mvm->stack_size-- < 0){
        printf("[MVM] StackUnderflow\n");
        exit(1);
    }

    return mvm->stack[mvm->stack_size];
}

size_t
mvm_gc(mvm_t* mvm){
    for(size_t i = 0; i < mvm->stack_size; i++){
        if(mvm->stack[i]){
            mvm_gc_mark(mvm->stack[i]);
        }
    }

    return mvm_gc_collect(mvm->alloc);
}

void
mvm_free(mvm_t* mvm){
    mvm->stack_size = 0;
    mvm_gc_sweep(mvm->alloc);
    mvm_alloc_free(mvm->alloc);
    free(mvm);
}