#include <types/mstringpool.h>
#include "types/mstringpool.h"

mstring_pool_t*
mstring_pool_create(){
    mstring_pool_t* pool;
    if((pool = malloc(sizeof(mstring_pool_t))) == NULL){
        return NULL;
    }

    pool->size = 0;
    pool->head = NULL;
    return pool;
}

mstring_t*
mstring_pool_internalize(mstring_pool_t* pool, mstring_t* str){
    mstring_pool_entry_t* entry = pool->head;
    while(entry){
        if(mstring_equals(entry->value, str)){
            mstring_free(str);
            return entry->value;
        }

        entry = entry->next;
    }

    if((entry = malloc(sizeof(mstring_pool_entry_t))) == NULL){
        return str;
    }

    entry->next = pool->head;
    entry->value = str;
    pool->head = entry;
    pool->size++;
    return str;
}

mstring_t*
mstring_pool_intern(mstring_pool_t* pool, byte* str){
    mstring_t* s = mstring_wrap(str);
    mstring_pool_entry_t* entry = pool->head;
    while(entry){
        if(mstring_equals(entry->value, s)){
            mstring_free(s);
            return entry->value;
        }

        entry = entry->next;
    }

    if((entry = malloc(sizeof(mstring_pool_entry_t))) == NULL){
        return s;
    }

    entry->next = pool->head;
    entry->value = s;
    pool->head = entry;
    pool->size++;
    return entry->value;
}

int
mstring_pool_contains(mstring_pool_t* pool, mstring_t* str){
    mstring_pool_entry_t* entry = pool->head;
    while(entry){
        if(mstring_equals(entry->value, str)){
            return 1;
        }

        entry = entry->next;
    }

    return 0;
}

int
mstring_pool_exists(mstring_pool_t* pool, byte* str){
    mstring_t* s = mstring_wrap(str);
    mstring_pool_entry_t* entry = pool->head;
    while(entry){
        if(mstring_equals(entry->value, s)){
            mstring_free(s);
            return 1;
        }

        entry = entry->next;
    }

    mstring_free(s);
    return 0;
}

void
mstring_pool_extern(mstring_pool_t* pool, byte* str){
    mstring_t* s = mstring_wrap(str);
    mstring_pool_entry_t* next = pool->head;
    mstring_pool_entry_t* last = NULL;

    while(next){
        if(mstring_equals(next->value, s)){
            mstring_pool_entry_t* tmp = next->next;

            if(last){
                last->next = tmp;
            } else{
                pool->head = tmp;
            }

            mstring_free(next->value);
            free(next);
            pool->size--;
            break;
        }

        last = next;
        next = next->next;
    }
}

void
mstring_pool_free(mstring_pool_t* pool){
    mstring_pool_entry_t* entry = pool->head;
    while(entry){
        mstring_pool_entry_t* tmp = entry;
        free(tmp->value);
        entry = tmp->next;
        free(tmp);
    }
    free(pool);
}