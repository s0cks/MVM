#include <mvm.h>
#include <string.h>

static const char* MVM_TRUES = "true";
static const char* MVM_FALSES = "false";

char*
mvm_bool_to_str(byte b){
    if(b){
        return (char*) MVM_TRUES;
    } else{
        return (char*) MVM_FALSES;
    }
}

mvm_t*
mvm_create(){
    mvm_t* mvm;
    if((mvm = malloc(sizeof(mvm_t))) == NULL){
        return NULL;
    }

    mvm->alloc = mvm_allocator_create(MVM_SS);
    mvm->string_pool = mstring_pool_create();
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
mvm_push_intern_string(mvm_t* mvm, byte* data){
    mvm_obj_t* str;
    if((str = mvm_alloc_new_intern_string(mvm->alloc, mvm->string_pool, data)) == NULL){
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
mvm_push_bool(mvm_t* mvm, byte data){
    mvm_obj_t* b;
    if((b = mvm_alloc_new_bool(mvm->alloc, data)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("[MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = b;
    return b;
}

mvm_obj_t*
mvm_push_null(mvm_t* mvm){
    mvm_obj_t* n;
    if((n = mvm_alloc_new_null(mvm->alloc)) == NULL){
        return NULL;
    }

    if(mvm->stack_size > MVM_SS){
        printf("[MVM] StackOverflow\n");
        exit(1);
    }

    mvm->stack[mvm->stack_size++] = n;
    return n;
}

mvm_obj_t*
mvm_pop(mvm_t* mvm){
    if(mvm->stack_size-- < 0){
        return NULL;
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
    mstring_pool_free(mvm->string_pool);
    free(mvm);
}

void
mvm_run(mvm_t* mvm){

}

void
mvm_assert(int exp, char* msg){
    if(!exp){
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
}

mstring_t*
mvm_obj_to_str(mvm_obj_t* obj){
    mstring_t* str = mstring_create();

    if(obj == NULL){
        mstring_put(str, (const byte*) "NULL", strlen("NULL"));
        return str;
    }

    if(mvm_is_array(obj)){
        mstring_putc(str, '[');
        for(size_t i = 0; i < mvm_array_size(obj); i++){
            mstring_t* tostr = mvm_obj_to_str(mvm_array_at(obj, i));
            mstring_putstr(str, tostr);
            mstring_free(tostr);

            if(i < mvm_array_size(obj) - 1){
                mstring_putc(str, ',');
            }
        }
        mstring_putc(str, ']');
    } else if(mvm_is_integer(obj)){
        mstring_printf(str, "%d", mvm_integer_value(obj));
    } else if(mvm_is_double(obj)){
        mstring_printf(str, "%lf", mvm_double_value(obj));
    } else if(mvm_is_string(obj)){
        mstring_printf(str, "\"%s\"", mstring_cstr(mvm_string_value(obj)));
    } else if(mvm_is_byte(obj)){
        mstring_printf(str, "%d", mvm_byte_value(obj));
    } else if(mvm_is_bool(obj)){
        mstring_printf(str, "%s", mvm_bool_to_str(mvm_bool_value(obj)));
    } else if(mvm_is_null(obj)){
        mstring_put(str, (const byte*) "NULL", strlen("NULL"));
    } else{
        mstring_printf(str, "<unknown type: %d>", obj->type);
    }

    return str;
}