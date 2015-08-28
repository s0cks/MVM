#ifndef MICROVM_MSTRING_H
#define MICROVM_MSTRING_H

#include "../mvm-private.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef MSTR_CHUNK_SIZE
#define MSTR_CHUNK_SIZE 10
#endif

#ifndef MSTR_INIT_SIZE
#define MSTR_INIT_SIZE 1024
#endif

typedef struct{
    byte* data;

    size_t size;
    size_t asize;
} mstring_t;

mstring_t* mstring_create() __attribute__((malloc));
mstring_t* mstring_slice(mstring_t* str, size_t offset, size_t len);
mstring_t* mstring_wrap(byte* str);

const char* mstring_cstr(mstring_t* str);
const char mstring_getc(mstring_t* str, size_t index);

int mstring_starts_with(mstring_t* str1, mstring_t* str2);
int mstring_equals(mstring_t* str1, mstring_t* str2);

void mstring_free(mstring_t* str);
void mstring_grow(mstring_t* str, size_t len);
void mstring_put(mstring_t* str, const byte* data, size_t size);
void mstring_putc(mstring_t* str, const byte data);
void mstring_putstr(mstring_t* str, mstring_t* data);
void mstring_printf(mstring_t* str, const char* fmt, ...) __attribute__((format));

#ifdef __cplusplus
};
#endif

#endif