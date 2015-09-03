#include <types/types.h>
#include <gc/allocator.h>

void
mvm_gc_mark(mvm_obj_t* obj){
    if(obj->marked){
        return;
    }

    obj->marked = 1;

    if(mvm_is_array(obj)){
        for(size_t i = 0; i < mvm_array_size(obj); i++){
            mvm_gc_mark(mvm_array_at(obj, i));
        }
    }
}

void
mvm_gc_sweep(mvm_allocator_t* alloc){
    mvm_obj_t** mot = &alloc->head;
    while(*mot){
        if(!(*mot)->marked){
            mvm_obj_t* unreached = *mot;
            *mot = unreached->next;
            mvm_type_free(unreached);
            alloc->num_objects--;
        } else{
            (*mot)->marked = 0;
            mot = &(*mot)->next;
        }
    }
}

size_t
mvm_gc_collect(mvm_allocator_t* alloc){
    size_t num_object = alloc->num_objects;
    mvm_gc_sweep(alloc);
    return num_object - alloc->num_objects;
}