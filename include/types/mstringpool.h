#ifndef MICROVM_MSTRINGPOOL_H
#define MICROVM_MSTRINGPOOL_H

#include "mstring.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _mstring_pool_entry_t{
    mstring_t* value;
    struct _mstring_pool_entry_t* next;
} mstring_pool_entry_t;

typedef struct{
    size_t size;
    mstring_pool_entry_t* head;
} mstring_pool_t;

mstring_pool_t* mstring_pool_create();
mstring_t* mstring_pool_internalize(mstring_pool_t* pool, mstring_t* str);
mstring_t* mstring_pool_intern(mstring_pool_t* pool, byte* str);
int mstring_pool_contains(mstring_pool_t* pool, mstring_t* str);
int mstring_pool_exists(mstring_pool_t* pool, byte* str);
void mstring_pool_extern(mstring_pool_t* pool, byte* str);
void mstring_pool_free(mstring_pool_t* pool);

#ifdef __cplusplus
};
#endif

#endif